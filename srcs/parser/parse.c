/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/14 08:54:37 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>//

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
		if (separator == 1)
		{
			make_command(&command_table, command_start, command_length);
			command_length = 0;
			command_start = tokens->next;
		}
		command_length++;
		tokens = tokens->next;
	}
}

void		make_command(t_list **table, t_list *start_node, int length)
{
	(void)table;
	printf("Start is: [%s], Length [%i]\n", (char *)start_node->content, length);
}
