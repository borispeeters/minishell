/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/15 11:49:24 by mpeerdem      ########   odam.nl         */
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
	parser.redirects = 0;
	parser.prev_sep = NO_SEPARATOR;
	while (tokens != NULL)
	{
		token = (char *)tokens->content;
		parse_metacharacter(&parser, token);
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
**	Check if the token is a meta character, and do the necessary actions.
*/

void		parse_metacharacter(t_parser *parser, char *token)
{
	if (ft_strcmp(token, ";") == 0)
		parser->sep = SEMICOLON;
	else if (ft_strcmp(token, "|") == 0)
		parser->sep = PIPE;
	else
		parser->sep = NO_SEPARATOR;
	if (ft_strcmp(token, ">") == 0 || ft_strcmp(token, ">>") == 0 || 
			ft_strcmp(token, "<") == 0)
		parser->redirects++;
}

/*
**	This function will take a few links of the token list and create a new
**	entry in the command table for it.
*/

void		make_command(t_list **table, t_parser *parser)
{
	t_command		*command;

	(void)table;
	command = prepare_command(parser);
	if (command == NULL)
		printf("Iets ging fout lmaoooo\n");
}
