#include <errno.h>
#include <signal.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	Quick utility function that either calls the search_path function if no
**	is found, and otherwise copies the command.
*/

static char		*get_path_from_arg(char *arg, t_env *env)
{
	char	*ret;

	if (ft_strchr(arg, '/') == NULL)
		return (search_path(arg, env->vars));
	ret = ft_strdup(arg);
	if (ret == NULL)
		shell_error_malloc();
	return (ret);
}

/*
**	This helper function will find the correct command, and return 1 if it
**	worked. If it failed, it will print an error and return 0.
*/

static int		find_command(t_shell *shell, t_executor *exec)
{
	exec->command = get_path_from_arg(exec->vars[0], shell->env);
	if (exec->command == NULL)
	{
		shell->exit_status = 127;
		shell_error_param("command not found", exec->vars[0]);
		return (1);
	}
	return (0);
}

void	signal_exec(int sig)
{
	signal(sig, signal_exec);
}

void			exec_binary(t_shell *shell, t_executor *exec)
{
	int	status;

	exec->vars = shell->cmd->vars;
	if (find_command(shell, exec) != 0)
		return ;
	exec->pid = fork();
	if (exec->pid < 0)
	{
		free(exec->command);
		shell_error(strerror(errno));
		return ;
	}
	if (exec->pid == 0)
	{
		execve(exec->command, exec->vars, shell->env->vars);
		shell_error_param(strerror(errno), exec->command);
		exit(127); // FIX LOLLL
	}
	waitpid(exec->pid, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		shell->sig = WTERMSIG(status);
		shell->exit_status = 128 + shell->sig;
	}
	if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
	}
	if (exec->command)
		free(exec->command);
}

void			exec_builtin(t_shell *shell, t_executor *exec, t_builtin builtin)
{
	if (shell->cmd->pipe == PIPE_NONE)
	{
		builtin(shell);
		return ;
	}
	exec->pid = fork();
	if (exec->pid < 0)
	{
		shell_error("fork failed");
		return ;
	}
	if (exec->pid == 0)
	{
		builtin(shell);
		exit(shell->exit_status);
	}
	wait(NULL);
}

void			exec_command(t_shell *shell, t_executor *exec)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(shell->cmd->vars[0], shell->b_name[i]) == 0)
		{
			exec_builtin(shell, exec, shell->builtin[i]);
			return ;
		}
		++i;
	}
	exec_binary(shell, exec);
}

int				duplicate_pipe(int fd, int stream)
{
	int	ret;

	ret = 0;
	if (fd != stream)
	{
		if (dup2(fd, stream) == -1)
		{
			shell_error(strerror(errno));
			ret = 1;
		}
		close(fd);
	}
	return (ret);
}

int				handle_pipes(t_executor *exec, t_list *table)
{
	int	ret;

	ret = 0;
	exec->fd[READ_END] = STDIN_FILENO;
	exec->fd[WRITE_END] = STDOUT_FILENO;
	if (table->next && pipe(exec->fd) == -1)
	{
		shell_error(strerror(errno));
		return (1);
	}
	ret += duplicate_pipe(exec->in, STDIN_FILENO);
	ret += duplicate_pipe(exec->fd[WRITE_END], STDOUT_FILENO);
	return (ret);
}

/*
**	Main execute loop. Will loop through the command table and will handle
**	pipes and redirects if necessary, then execute the command.
*/

void			execute_loop(t_shell *shell, t_list *table, t_env *env)
{
	t_executor	exec;
	int			bak[2];

	shell->env = env;
	exec.in = STDIN_FILENO;
	signal(SIGINT, signal_exec);
	signal(SIGQUIT, signal_exec);
	while (table)
	{
		shell->sig = 0;
		exec.command = NULL;
		shell->cmd = table->content;
		bak[READ_END] = dup(STDIN_FILENO);
		bak[WRITE_END] = dup(STDOUT_FILENO);
		if (handle_pipes(&exec, table) == 0 && output_redir(shell->cmd) == 0 && input_redir(shell->cmd) == 0)
		{
			exec_command(shell, &exec);
		}
		if (table->next)
			exec.in = exec.fd[READ_END];
		if (dup2(bak[READ_END], STDIN_FILENO) == -1)
		{
			shell_error(strerror(errno));
		}
		if (dup2(bak[WRITE_END], STDOUT_FILENO) == -1)
		{
			shell_error(strerror(errno));
		}
		close(bak[READ_END]);
		close(bak[WRITE_END]);
		if (shell->sig == SIGINT)
			ft_putchar_fd('\n', 1);
		if (shell->sig == SIGQUIT)
			ft_putendl_fd("Quit: 3", 1);
		table = table->next;
	}
}
