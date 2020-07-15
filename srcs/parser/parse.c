/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/15 14:34:49 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>//

// DEBUG
void	print_table(t_list *table)
{
	t_command	*command;

	printf("\n_____COMMAND TABLE_____\n\n");
	while (table != NULL)
	{
		command = (t_command *)table->content;
		printf("Element.\n");
		table = table->next;
	}
	printf("\n_____COMMAND TABLE_____\n");
}

/*
**	The main parse function, will loop over the list and delegate work to
**	other functions.
*/

void		parse(t_list *tokens)
{
	char			*token;
	t_parser		parser;
	t_list			*comm_table;

	comm_table = NULL;
	parser.start = tokens;
	parser.length = 0;
	parser.prev_sep = NO_SEPARATOR;
	while (tokens != NULL)
	{
		token = (char *)tokens->content;
		parser.sep = is_separator(token);
		if (parser.sep)
		{
			make_command(&comm_table, &parser);
			parser.prev_sep = parser.sep;
			parser.length = -1;
			parser.start = tokens->next;
		}
		parser.length++;
		tokens = tokens->next;
	}
	if (parser.length > 0)
		make_command(&comm_table, &parser);
	
	//
	print_table(comm_table);
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
	prev = NO_REDIRECT;
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

void		make_command(t_list **table, t_parser *parser)
{
	t_command		*command;
	int				length;

	(void)table;
	length = validate_command(parser);
	printf("Length? [%i]\n", length);
	command = prepare_command(parser, length);
	if (command == NULL)
		printf("Iets ging fout lmaoooo\n");
}
