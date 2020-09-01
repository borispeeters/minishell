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
	if (ft_strchr(arg, '/') == NULL)
		return (search_path(arg, env->vars));
	return (ft_strdup(arg));
}

/*
**	This helper function will find the correct command, and return 1 if it
**	worked. If it failed, it will print an error and return 0.
*/

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

/*
**	Main execute loop. Will loop through the command table and will handle
**	pipes and redirects if necessary, then execute the command.
*/

void		execute(t_list *table, t_env *env)
{
	t_executor	exec;

	exec.in = 0;
	exec.fd[1] = 1;
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
			free(exec.command);
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
			if (exec.fd[1] != 1)
			{
				dup2(exec.fd[1], 1);
				close(exec.fd[1]);
			}
			if (output_redir((t_command*)table->content) ||
					input_redir((t_command*)table->content))
			{
				printf("SAAAUUUS\n");
				return ;
			}
			execve(exec.command, exec.vars, env->vars);
		}
		wait(NULL);
		free(exec.command);
		if (table->next)
		{
			close(exec.fd[1]);
			exec.in = exec.fd[0];
		}
		table = table->next;
	}
}
