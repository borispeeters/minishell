/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:27 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:27 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	Quick utility function that either calls the search_path function if no
**	is found, and otherwise copies the command.
*/

static char	*get_path_from_arg(char *arg, t_env *env)
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

static int	find_command(t_shell *shell, t_executor *exec)
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

/*
**	This function handles the execution of a binary file in a child process.
*/

static void	exec_binary(t_shell *shell, t_executor *exec)
{
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
		exit(126);
	}
	wait_cmd(shell, exec);
	if (exec->command)
		free(exec->command);
}

/*
**	This function forks a new process if we're in a pipeline
**	and then executes the correct builtin.
*/

static void	exec_builtin(t_shell *shell, t_executor *exec, t_builtin builtin)
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
	wait_cmd(shell, exec);
}

/*
**	This function will look for a builtin
**	and if can't find one will execute a command.
*/

void		exec_command(t_shell *shell, t_executor *exec)
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
