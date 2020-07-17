/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 10:00:57 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/17 17:59:41 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"

void	free_content(void *content)
{
	free(content);
}

int		is_space(int c)
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
**	This function will return an enum for which kind of separator the token is.
*/

t_separator		is_separator(char *token)
{
	if (ft_strcmp(token, ";") == 0)
		return (SEMICOLON);
	if (ft_strcmp(token, "|") == 0)
		return (PIPE);
	return (NO_SEPARATOR);
}

/*
**	This function will return an enum for which kind of redirect the token is.
*/

t_redirect		is_redirect(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT_TRUNC);
	if (ft_strcmp(token, ">>") == 0)
		return (REDIRECT_OUT_APPEND);
	return (NO_REDIRECT);
}
