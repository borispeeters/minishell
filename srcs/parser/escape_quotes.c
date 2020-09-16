/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   escape_quotes.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:54 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:55 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	Calculates the amount of quotes and backslashes in s.
*/

int			count_quote_escape(char const *s)
{
	int	quotes;
	int	i;

	quotes = 0;
	i = 0;
	while (s[i])
	{
		if (is_quote_escape(s[i]))
			++quotes;
		++i;
	}
	return (quotes);
}

/*
**	This function will insert a backslash in string s at index i.
*/

static void	insert_escape(char *s, int i)
{
	int	len;

	len = ft_strlen(s);
	s[len + 1] = '\0';
	while (len > i)
	{
		s[len] = s[len - 1];
		--len;
	}
	s[i] = '\\';
}

/*
**	This function will insert a backslash in front of quotes
**	and the backslash itself.
*/

void		escape_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (is_quote_escape(s[i]))
		{
			insert_escape(s, i);
			++i;
		}
		++i;
	}
}
