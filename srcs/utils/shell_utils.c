/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:31 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:32 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	A simple function that frees the given parameter
**	that can be used as a function pointer.
*/

void		free_content(void *content)
{
	free(content);
}

/*
**	This function will return non-zero if c is a whitespace character,
**	zero otherwise.
*/

int			is_space(int c)
{
	return (c == ' ' || c == '\t');
}

/*
**	This function will return non-zero if c is a metacharacter,
**	zero otherwise.
*/

int			is_metacharacter(int c)
{
	char	metachar[6];
	int		i;

	ft_strlcpy(metachar, "\n|;<>", 6);
	i = 0;
	while (metachar[i])
	{
		if (c == metachar[i])
			return (1);
		++i;
	}
	return (0);
}

int			is_quote_escape(int c)
{
	return (c == '\'' || c == '\"' || c == '\\');
}
