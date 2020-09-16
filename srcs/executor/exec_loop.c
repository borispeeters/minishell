/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exec_loop.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:24 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:25 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function makes backup file descriptors
**	that point to the standard input and output.
*/

int				backup_stdio(t_executor *exec)
{
	exec->bak[READ_END] = dup(STDIN_FILENO);
	exec->bak[WRITE_END] = dup(STDOUT_FILENO);
	if (exec->bak[READ_END] == -1 || exec->bak[WRITE_END] == -1)
	{
		shell_error(strerror(errno));
		return (1);
	}
	return (0);
}

/*
**	This function will restore the object descriptors
**	to the standard input and output.
*/

int				restore_stdio(t_executor *exec)
{
	if (dup2(exec->bak[READ_END], STDIN_FILENO) == -1)
	{
		shell_error(strerror(errno));
		return (1);
	}
	if (dup2(exec->bak[WRITE_END], STDOUT_FILENO) == -1)
	{
		shell_error(strerror(errno));
		return (1);
	}
	close(exec->bak[READ_END]);
	close(exec->bak[WRITE_END]);
	return (0);
}

/*
**	Utility function to make the output of signals more realistic.
*/

void			write_signal(t_shell *shell)
{
	if (shell->sig == SIGINT)
		ft_putchar_fd('\n', STDOUT_FILENO);
	if (shell->sig == SIGQUIT)
		ft_putendl_fd("Quit: 3", STDOUT_FILENO);
}

/*
**	Main execute loop. Will loop through the command table and will handle
**	pipes and redirects if necessary, then execute the command.
*/

void			execute_loop(t_shell *shell, t_list *table)
{
	t_executor	exec;

	exec.in = STDIN_FILENO;
	signal(SIGINT, signal_exec);
	signal(SIGQUIT, signal_exec);
	while (table)
	{
		shell->sig = 0;
		exec.command = NULL;
		shell->cmd = table->content;
		if (backup_stdio(&exec) != 0)
			continue ;
		if (handle_pipes(&exec, table) == 0 && output_redir(shell->cmd) == 0
		&& input_redir(shell->cmd) == 0 && shell->cmd->vars[0] != NULL)
		{
			exec_command(shell, &exec);
		}
		if (table->next)
			exec.in = exec.fd[READ_END];
		while (restore_stdio(&exec) != 0)
			continue ;
		write_signal(shell);
		table = table->next;
	}
}
