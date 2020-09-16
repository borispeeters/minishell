/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:20:37 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:38 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	Builtin echo will display all its arguments
**	followed by a newline, unless the -n option is specified.
*/

void	builtin_echo(t_shell *shell)
{
	int	i;
	int	print_newline;

	print_newline = 1;
	i = 1;
	if (shell->cmd->vars[i] && ft_strcmp(shell->cmd->vars[i], "-n") == 0)
	{
		print_newline = 0;
		++i;
	}
	while (shell->cmd->vars[i])
	{
		ft_putstr_fd(shell->cmd->vars[i], STDOUT_FILENO);
		++i;
		if (shell->cmd->vars[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
