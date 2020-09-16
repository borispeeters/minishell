/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_removal_states.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:06 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:07 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	This function will return non-zero if c is a character
**	that when followed by a backslash will remove the backslash
**	in double quotes, zero otherwise.
*/

static int	double_quoted_backslash(int c)
{
	return (c == '\"' || c == '\\' || c == '$' || c == '\n');
}

/*
**	This function will remove a single character from a string.
*/

static void	remove_character(char **str, int i)
{
	char	*tmp;

	tmp = malloc(sizeof(*tmp) * ft_strlen(*str));
	if (tmp == NULL)
		shell_error_malloc();
	ft_strlcpy(tmp, *str, i + 1);
	ft_strlcat(tmp, *str + i + 1, ft_strlen(*str));
	free(*str);
	*str = tmp;
}

/*
**	This function will remove a single quote if necessary.
*/

int			qr_single_quote(t_expansion *exp, char **vars, int i)
{
	exp_single_quote(exp);
	if (exp->quote != DBL_QUOTE && exp->escape != ESCAPE)
	{
		remove_character(vars, i);
		return (1);
	}
	return (0);
}

/*
**	This function will remove a double quote if necessary.
*/

int			qr_double_quote(t_expansion *exp, char **vars, int i)
{
	exp_double_quote(exp);
	if (exp->quote != SNGL_QUOTE && exp->escape != ESCAPE)
	{
		remove_character(vars, i);
		return (1);
	}
	return (0);
}

/*
**	This function will remove an escape character if necessary.
*/

int			qr_escape(t_expansion *exp, char **vars, int i)
{
	exp_escape_char(exp);
	if (exp->escape == ESCAPE)
	{
		if ((exp->quote == DBL_QUOTE &&
		double_quoted_backslash((*vars)[i + 1])) || exp->quote == NO_QUOTE)
		{
			remove_character(vars, i);
			return (1);
		}
	}
	return (0);
}
