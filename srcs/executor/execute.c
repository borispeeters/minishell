#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
void	execute_old(t_list *table, t_env *env)
{
	t_command	*command;
	char		**vars;
	pid_t		pid;
	char		*cmd;
	int			in_bak;
	int			out_bak;

	command = (t_command*)table->content;
	vars = command->vars;
	cmd = (ft_strchr(vars[0], '/') == NULL) ? search_path(vars[0], env->vars) : ft_strdup(vars[0]);
	if (cmd == NULL)
	{
		write(2, "minishell: command not found\n", 29);
		return ;
	}
	in_bak = dup(0);
	out_bak = dup(1);
	if (output_redir(command) != 0 || input_redir(command) != 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, vars, env->vars);
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else if (pid < 0)
	{
		write(2, "minishell: failed to fork child process\n", 40);
	}
	dup2(in_bak, 0);
	dup2(out_bak, 1);
	free(cmd);
}*/

static char		*get_path_from_arg(char *arg, t_env *env)
{
	if (ft_strchr(arg, '/') == NULL)
		return (search_path(arg, env->vars));
	return (ft_strdup(arg));
}

static int		find_command(t_list *table, t_executor *exec, t_env *env)
{
	exec->vars = ((t_command*)table->content)->vars;
	exec->command = get_path_from_arg(exec->vars[0], env);
	if (exec->command == NULL)
	{
		shell_error_param("command not found", exec->vars[0]);
		return (0);
	}
	return (1);
}

void		execute(t_list *table, t_env *env)
{
	t_executor		exec;

	exec.in = 0;
	while (table)
	{
		if (!find_command(table, &exec, env))
			return ;
		if (table->next)
			pipe(exec.fd);
		// builtin?
		exec.pid = fork();
		if (exec.pid < 0)
		{
			shell_error("fork failed");
			return ;
		}
		if (exec.pid == 0)
		{
			if (exec.in != 0)
			{
				dup2(exec.in, 0);
				close(exec.in);
			}
			if (table->next && exec.fd[1] != 1)
			{
				dup2(exec.fd[1], 1);
				close(exec.fd[1]);
			}
			execve(exec.command, exec.vars, env->vars);
		}
		wait(NULL);
		if (table->next)
		{
			close(exec.fd[1]);
			exec.in = exec.fd[0];
		}
		table = table->next;
	}
}
