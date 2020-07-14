/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/14 10:12:29 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>//

/*
**	The main parse function, will loop over the list and delegate work to
**	other functions.
*/

void		parse(t_list *tokens)
{
	char	*token;
	t_list	*command_start;
	int		command_length;
	int		separator;
	t_list	*command_table;

	command_table = NULL;
	command_start = tokens;
	command_length = 0;
	while (tokens != NULL)
	{
		token = (char *)tokens->content;
		separator = is_command_separator(token);
		if (separator)
		{
			make_command(&comm_table, comm_start, comm_length, separator);
			command_length = -1;
			command_start = tokens->next;
		}
		command_length++;
		tokens = tokens->next;
	}
	if (command_length > 0)
		make_command(&command_table, command_start, command_length);
}

/*
**	This function will take a few links of the token list and create a new
**	entry in the command table for it.
*/

void		make_command(t_list **table, t_list *start_node, int length,
				int separator)
{
	(void)table;
	printf("Start is: [%s], Length [%i]\n", (char *)start_node->content, length);
}
