/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:20:42 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:43 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	Builtin env will display all the variables in the environment list.
*/

void	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->env->length)
	{
		if (ft_strchr(shell->env->vars[i], '='))
			ft_putendl_fd(shell->env->vars[i], STDOUT_FILENO);
		++i;
	}
}
