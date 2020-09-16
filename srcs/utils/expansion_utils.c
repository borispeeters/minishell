/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expansion_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:24 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:24 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	This function will return non-zero if c is a valid character
**	for the name of an environment variable, zero otherwise.
*/

int		is_env(int c)
{
	return (ft_isalnum(c) || c == '_');
}

/*
**	This function is called when an escape character is encountered
**	in the expander.
*/

void	exp_escape_char(t_expansion *exp)
{
	if (exp->quote != SNGL_QUOTE)
	{
		if (exp->escape == NO_ESCAPE)
			exp->escape = ESCAPE;
		else if (exp->escape == ESCAPE)
			exp->escape = NO_ESCAPE;
	}
}

/*
**	This function is called when a double quote is encountered
**	in the expander.
*/

void	exp_double_quote(t_expansion *exp)
{
	if (exp->escape != ESCAPE)
	{
		if (exp->quote == DBL_QUOTE)
			exp->quote = NO_QUOTE;
		else if (exp->quote == NO_QUOTE)
			exp->quote = DBL_QUOTE;
	}
}

/*
**	This function is called when a single quote is encountered
**	in the expander.
*/

void	exp_single_quote(t_expansion *exp)
{
	if (exp->quote == SNGL_QUOTE)
		exp->quote = NO_QUOTE;
	else if (exp->quote == NO_QUOTE && exp->escape != ESCAPE)
		exp->quote = SNGL_QUOTE;
}

/*
**	This function will handle escape character and quotes.
*/

void	exp_quote_handler(t_expansion *exp, char c)
{
	if (c == '\\')
		exp_escape_char(exp);
	if (c == '\"')
		exp_double_quote(exp);
	if (c == '\'')
		exp_single_quote(exp);
}
