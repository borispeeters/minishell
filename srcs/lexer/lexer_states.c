/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 11:08:52 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/15 14:39:43 by bpeeters      ########   odam.nl         */
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

void	in_token(t_lexer *lex, char *line, t_list **head)
{
	if (is_metacharacter(*line))
	{
		ft_lstadd_back(head, \
		ft_lstnew(ft_substr(lex->token_start, 0, lex->token_len)));
		lex->token_start = line;
		lex->token_len = 0;
		lex->token_active = META;
	}
	if (is_space(*line) && lex->quote == NO_QUOTE)
	{
		ft_lstadd_back(head, \
		ft_lstnew(ft_substr(lex->token_start, 0, lex->token_len)));
		lex->token_active = INACTIVE;
	}
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

void	meta_encounter(t_lexer *lex, char *line, t_list **head)
{
	if (*line == '>')
		return ;
	ft_lstadd_back(head, \
	ft_lstnew(ft_substr(lex->token_start, 0, lex->token_len)));
	if (is_space(*line))
		lex->token_active = INACTIVE;
	else
	{
		lex->token_start = line;
		lex->token_len = 0;
		if (!is_metacharacter(*line))
			lex->token_active = ACTIVE;
	}
}
