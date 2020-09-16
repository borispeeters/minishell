/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_exit.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:20:47 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:48 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This helper function will check if the string given as input parameter
**	only contains digits.
*/

static int	str_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		++i;
	}
	return (1);
}

/*
**	Builtin exit will exit the shell with the current exit status,
**	or with the number given as argument.
*/

void		builtin_exit(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->vars[i])
	{
		if (i == 2)
		{
			shell_error_param("too many arguments", "exit");
			shell->exit_status = 1;
			return ;
		}
		if (!str_digit(shell->cmd->vars[i]))
		{
			shell_error_builtin_param("numeric argument required", "exit",
			shell->cmd->vars[i]);
			shell->exit_status = 255;
			break ;
		}
		shell->exit_status = ft_atoi(shell->cmd->vars[i]);
		++i;
	}
	shell->status = 0;
}
