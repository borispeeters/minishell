/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_states.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:46 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:46 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	This function is called when a non-special character is encountered
**	and the token state is active.
*/

void	in_token(t_lexer *lex, char *line, t_list **head)
{
	if (lex->escape != ESCAPE)
	{
		if (is_metacharacter(*line))
		{
			add_new_token(lex, head);
			lex->token_start = line;
			lex->token_len = 0;
			lex->token_active = META;
		}
		if (is_space(*line) && lex->quote == NO_QUOTE)
		{
			add_new_token(lex, head);
			lex->token_active = INACTIVE;
		}
	}
}

/*
**	This function is called when a non-special character is encountered
**	and the token state is inactive.
*/

void	out_of_token(t_lexer *lex, char *line)
{
	if (!is_space(*line))
	{
		lex->token_start = line;
		lex->token_len = 0;
		lex->token_active = ACTIVE;
		if (is_metacharacter(*line))
			lex->token_active = META;
	}
}

/*
**	This function is called when a metacharacter is encountered.
*/

void	meta_encounter(t_lexer *lex, char *line, t_list **head)
{
	if (*line == '>')
		return ;
	add_new_token(lex, head);
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
