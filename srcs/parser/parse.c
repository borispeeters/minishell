/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/14 12:43:55 by mpeerdem      ########   odam.nl         */
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
	while (tokens != NULL)
	{
		token = (char *)tokens->content;
		parser.sep = is_command_separator(token);
		if (parser.sep)
		{
			make_command(&comm_table, &parser);
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
**	This function will take a few links of the token list and create a new
**	entry in the command table for it.
*/

void		make_command(t_list **table, t_parser *parser)
{
	(void)table;
	if (parser->length == 0 && parser->sep != NO_SEPARATOR)
		printf("OEPS GING FOUT! :( \n");
	else
	{
		printf("Start is: [%s], Length [%i]\n", (char *)parser->start->content, parser->length);
		printf("Separator is %i\n", (int)parser->sep);
	}
}
