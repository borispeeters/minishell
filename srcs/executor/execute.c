#include <errno.h>
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

static int		find_command(t_executor *exec, t_env *env)
{
	exec->command = get_path_from_arg(exec->vars[0], env);
	if (exec->command == NULL)
	{
		shell_error_param("command not found", exec->vars[0]);
		return (1);
	}
	return (0);
}

void			exec_binary(t_shell *shell, t_env *env, t_command *cmd,
					t_executor *exec)
{
	(void)shell;
	exec->vars = cmd->vars;
	if (find_command(exec, env) != 0)
		return ;
	exec->pid = fork();
	if (exec->pid < 0)
	{
		free(exec->command);
		shell_error("fork failed");
		return ;
	}
	if (exec->pid == 0)
	{
		execve(exec->command, exec->vars, env->vars);
		shell_error_param(strerror(errno), exec->command);
		exit(127); // FIX LOLLL
	}
	wait(NULL);
	if (exec->command)
		free(exec->command);
}

int				is_builtin(t_shell *shell, t_command *cmd)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->vars[0], shell->b_name[i]) == 0)
			return (1);
		++i;
	}
	return (0);
}

void			exec_builtin(t_shell *shell, t_env *env, t_command *cmd,
					t_builtin builtin)
{
	builtin(shell, env, cmd);
}

int				exec_command(t_shell *shell, t_env *env, t_command *cmd,
					t_executor *exec)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_strcmp(cmd->vars[0], shell->b_name[i]) == 0)
		{
			exec_builtin(shell, env, cmd, shell->builtin[i]);
			// shell->builtin[i](shell, env, cmd);
			return (0);
		}
		++i;
	}
	exec_binary(shell, env, cmd, exec);
	return (1);
}

void			handle_pipes(t_executor *exec, t_list *table)
{
	if (table->next)
		pipe(exec->fd);
	if (exec->in != STDIN_FILENO)
	{
		dup2(exec->in, STDIN_FILENO);
		close(exec->in);
	}
	if (exec->fd[1] != 1)
	{
		dup2(exec->fd[1], STDOUT_FILENO);
		close(exec->fd[1]);
	}
}

/*
**	Main execute loop. Will loop through the command table and will handle
**	pipes and redirects if necessary, then execute the command.
*/

void			execute_loop(t_shell *shell, t_list *table, t_env *env)
{
	t_executor	exec;
	int			bak[2];
	t_command	*command;

	exec.in = STDIN_FILENO;
	exec.fd[1] = STDOUT_FILENO;
	while (table)
	{
		exec.command = NULL;
		command = table->content;
		bak[0] = dup(STDIN_FILENO);
		bak[1] = dup(STDOUT_FILENO);
		handle_pipes(&exec, table);
		if (output_redir(command) || input_redir(command))
		{
			printf("SAAAUUUS\n");
			return ;
		}
		exec_command(shell, env, command, &exec);
		if (table->next)
			exec.in = exec.fd[0];
		dup2(bak[0], STDIN_FILENO);
		dup2(bak[1], STDOUT_FILENO);
		close(bak[0]);
		close(bak[1]);
		table = table->next;
	}
}
