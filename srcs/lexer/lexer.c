/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:41 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:41 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will add a token to the end of the list.
*/

void		add_new_token(t_lexer *lex, t_list **head)
{
	char	*token;
	t_list	*node;

	token = ft_substr(lex->token_start, 0, lex->token_len);
	if (token == NULL)
		shell_error_malloc();
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		shell_error_malloc();
	}
	ft_lstadd_back(head, node);
}

/*
**	This function will loop through the input line
**	and call the appropriate functions.
*/

static void	lex_loop(t_lexer *lex, char *line, t_list **head)
{
	if (*line == '\\')
		escape_char(lex, line);
	if (*line == '\"' && lex->quote != SNGL_QUOTE)
		double_quote(lex, line);
	else if (*line == '\'' && lex->quote != DBL_QUOTE)
		single_quote(lex, line);
	else if (lex->token_active == ACTIVE && lex->quote == NO_QUOTE)
		in_token(lex, line, head);
	else if (lex->token_active == INACTIVE)
		out_of_token(lex, line);
	else if (lex->token_active == META && lex->quote == NO_QUOTE)
		meta_encounter(lex, line, head);
	if (lex->escape == ESCAPE && *line != '\\')
		lex->escape = NO_ESCAPE;
	if (lex->token_active >= ACTIVE)
		++lex->token_len;
}

/*
**	This function initiates some values for the lexer.
*/

static void	init_lexer(t_list **head, t_lexer *lex)
{
	*head = NULL;
	lex->quote = NO_QUOTE;
	lex->token_start = NULL;
	lex->token_len = 0;
	lex->token_active = INACTIVE;
	lex->escape = NO_ESCAPE;
}

/*
**	The main lexer function.
*/

t_list		*lexer(char *line)
{
	t_list	*head;
	t_lexer	lex;

	init_lexer(&head, &lex);
	while (*line)
	{
		lex_loop(&lex, line, &head);
		++line;
	}
	if (lex.token_active >= ACTIVE)
		add_new_token(&lex, &head);
	if (lex.quote != NO_QUOTE)
	{
		shell_error("multiline commands are not supported");
		ft_lstclear(&head, free_content);
	}
	return (head);
}
