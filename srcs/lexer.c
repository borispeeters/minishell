/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 09:59:32 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/07 11:10:38 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

char	*lex_loop(t_lexer *lex, char *line, t_list **head)
{
	if (*line == '\"' && lex->quote != SNGL_QUOTE)
		double_quote(lex, line);
	else if (*line == '\'' && lex->quote != DBL_QUOTE)
		single_quote(lex, line);
	if (lex->token_active == ACTIVE && lex->quote == NO_QUOTE)
		in_token(lex, line, head);
	else if (lex->token_active == INACTIVE)
		out_of_token(lex, line);
	else if (lex->token_active == META && lex->quote == NO_QUOTE)
		meta_encounter(lex, line, head);
	if (lex->token_active >= ACTIVE)
		++lex->token_len;
	return (++line);
}

t_list	*lexer(char *line)
{
	t_list	*head;
	t_lexer	lex;

	head = NULL;
	lex.quote = NO_QUOTE;
	lex.token_start = NULL;
	lex.token_len = 0;
	lex.token_active = INACTIVE;
	while (*line)
		line = lex_loop(&lex, line, &head);
	if (lex.token_active >= ACTIVE)
		ft_lstadd_back(&head, \
		ft_lstnew(ft_substr(lex.token_start, 0, lex.token_len)));
	return (head);
}
