/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 11:08:52 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/16 09:00:56 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

void	double_quote(t_lexer *lex, char *line)
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

void	single_quote(t_lexer *lex, char *line)
{
	if (lex->quote == SNGL_QUOTE)
		lex->quote = NO_QUOTE;
	else if (lex->quote == NO_QUOTE)
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

int		in_token(t_lexer *lex, char *line, t_list **head)
{
	if (is_metacharacter(*line))
	{
		if (add_new_token(lex, head) == -1)
			return (-1);
		lex->token_start = line;
		lex->token_len = 0;
		lex->token_active = META;
	}
	if (is_space(*line) && lex->quote == NO_QUOTE)
	{
		if (add_new_token(lex, head) == -1)
			return (-1);
		lex->token_active = INACTIVE;
	}
	return (0);
}

void	out_of_token(t_lexer *lex, char *line)
{
	if (is_metacharacter(*line))
	{
		lex->token_start = line;
		lex->token_len = 0;
		lex->token_active = META;
	}
	else if (!is_space(*line))
	{
		lex->token_start = line;
		lex->token_len = 0;
		lex->token_active = ACTIVE;
	}
}

int		meta_encounter(t_lexer *lex, char *line, t_list **head)
{
	if (*line == '>')
		return (0);
	if (add_new_token(lex, head) == -1)
		return (-1);
	if (is_space(*line))
		lex->token_active = INACTIVE;
	else
	{
		lex->token_start = line;
		lex->token_len = 0;
		if (!is_metacharacter(*line))
			lex->token_active = ACTIVE;
	}
	return (0);
}
