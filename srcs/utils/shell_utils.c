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

/*
**	This function will return an enum for which kind of separator the token is.
*/

t_separator	is_separator(char *token)
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

t_redirect	is_redirect(char *token)
{
	if (ft_strcmp(token, "<") == 0)
		return (REDIRECT_IN);
	if (ft_strcmp(token, ">") == 0)
		return (REDIRECT_OUT_TRUNC);
	if (ft_strcmp(token, ">>") == 0)
		return (REDIRECT_OUT_APPEND);
	return (NO_REDIRECT);
}
