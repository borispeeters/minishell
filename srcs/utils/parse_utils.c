#include "libft.h"
#include "minishell.h"

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
