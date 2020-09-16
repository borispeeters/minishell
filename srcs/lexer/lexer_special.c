/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_special.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:43 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:44 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function is called when a double quote is encountered
**	during the lexing phase.
*/

void	double_quote(t_lexer *lex, char *line)
{
	if (lex->escape != ESCAPE)
	{
		if (lex->quote == DBL_QUOTE)
			lex->quote = NO_QUOTE;
		else if (lex->quote == NO_QUOTE)
		{
			lex->quote = DBL_QUOTE;
			if (lex->token_active == INACTIVE)
			{
				lex->token_active = ACTIVE;
				lex->token_start = line;
				lex->token_len = 0;
			}
		}
	}
}

/*
**	This function is called when a single quote is encountered
**	during the lexing phase.
*/

void	single_quote(t_lexer *lex, char *line)
{
	if (lex->quote == SNGL_QUOTE)
		lex->quote = NO_QUOTE;
	else if (lex->quote == NO_QUOTE)
	{
		if (lex->escape != ESCAPE)
		{
			lex->quote = SNGL_QUOTE;
			if (lex->token_active == INACTIVE)
			{
				lex->token_active = ACTIVE;
				lex->token_start = line;
				lex->token_len = 0;
			}
		}
	}
}

/*
**	This function is called when an escape character is encountered
**	during the lexing phase.
*/

void	escape_char(t_lexer *lex, char *line)
{
	if (lex->quote != SNGL_QUOTE)
	{
		if (lex->escape == NO_ESCAPE)
		{
			lex->escape = ESCAPE;
			if (lex->token_active == INACTIVE)
			{
				lex->token_start = line;
				lex->token_len = 0;
				lex->token_active = ACTIVE;
			}
		}
		else if (lex->escape == ESCAPE)
		{
			lex->escape = NO_ESCAPE;
		}
	}
}
