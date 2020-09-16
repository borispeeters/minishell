/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:59 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:59 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	Helper function for the parse loop that handles the separators. Returns
**	1 if a ; was encountered, 0 otherwise.
*/

static int	handle_separator(t_parser *parser, t_list **comm_table,
				t_list **tokens)
{
	t_list	*tmp;
	char	*token;

	token = (char*)(*tokens)->content;
	parser->sep = is_separator(token);
	if (parser->sep)
	{
		create_command(comm_table, parser);
		tmp = parser->start;
		parser->prev_sep = parser->sep;
		parser->start = (*tokens)->next;
		free(tmp->content);
		free(tmp);
	}
	if (parser->sep == SEMICOLON)
	{
		*tokens = (*tokens)->next;
		return (1);
	}
	*tokens = (*tokens)->next;
	return (0);
}

/*
**	The main parse function, will loop over the list and delegate work to
**	other functions.
*/

t_list		*parse(t_list **tokens)
{
	t_parser		parser;
	t_list			*comm_table;
	int				found_semicolon;

	comm_table = NULL;
	parser.start = *tokens;
	parser.prev_sep = NO_SEPARATOR;
	while (*tokens != NULL)
	{
		found_semicolon = handle_separator(&parser, &comm_table, tokens);
		if (found_semicolon)
			return (comm_table);
	}
	if (parser.start != NULL)
		create_command(&comm_table, &parser);
	return (comm_table);
}

/*
**	This function will check if the format of the command is valid, that mostly
**	means no double redirects. Will return 0 if invalid, otherwise the length
**	of the var list.
*/

int			validate_command(t_parser *parser)
{
	t_redirect	prev;
	t_redirect	curr;
	int			count;
	t_list		*node;

	count = 0;
	curr = NO_REDIRECT;
	node = parser->start;
	while (node != NULL && !is_separator((char *)node->content))
	{
		count++;
		prev = curr;
		curr = is_redirect((char *)node->content);
		if (curr != NO_REDIRECT)
			count -= 2;
		if (prev != NO_REDIRECT && curr != NO_REDIRECT)
			return (0);
		node = node->next;
	}
	if (curr != NO_REDIRECT)
		return (0);
	return (count);
}

/*
**	This function will take a few links of the token list and create a new
**	entry in the command table for it.
*/

void		create_command(t_list **table, t_parser *parser)
{
	t_list			*new;
	int				length;

	length = validate_command(parser);
	new = prepare_command(length);
	parse_command((t_command*)new->content, parser);
	ft_lstadd_back(table, new);
}

/*
**	This will loop over the tokens and assign the correct values to fields in
**	the command struct.
*/

void		parse_command(t_command *command, t_parser *parser)
{
	int			vars_parsed;
	t_redirect	redirect;
	t_list		*tmp;

	vars_parsed = 0;
	while (parser->start && !is_separator((char *)parser->start->content))
	{
		redirect = is_redirect((char*)parser->start->content);
		if (redirect != NO_REDIRECT)
			handle_redirect(command, parser, redirect);
		else
		{
			*(command->vars + vars_parsed) = parser->start->content;
			vars_parsed++;
		}
		tmp = parser->start;
		parser->start = parser->start->next;
		free(tmp);
	}
	if (parser->sep == PIPE)
		command->pipe ^= PIPE_OUT;
	if (parser->prev_sep == PIPE)
		command->pipe ^= PIPE_IN;
}
