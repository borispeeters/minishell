/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 10:00:57 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/14 11:30:39 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

int				is_space(int c)
{
	return (c == ' ' || c == '\t');
}

int				is_metacharacter(int c)
{
	char	metachar[8];
	int		i;

	ft_strlcpy(metachar, "\n|;()<>", 8);
	i = 0;
	while (metachar[i])
	{
		if (c == metachar[i])
			return (1);
		++i;
	}
	return (0);
}

/*
**	Small utility function that returns the type of separator it is (enum).
*/

t_separator		is_command_separator(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (SEMICOLON);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	return (NO_SEPARATOR);
}
