/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 11:43:08 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/15 11:51:38 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function will malloc a command structure, and the vars array in it.
*/
t_command	*prepare_command(t_parser *parser)
{
	t_command	*command;
	int			var_count;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	var_count = parser->length + 1 - parser->redirects * 2;
	command->vars = malloc_var_array(var_count);
	if (command->vars == NULL)
	{
		free_command(command);
		return (NULL);
	}
	return (command);
}

/*
**	This function will free a command struct and its variables.
*/

void		free_command(t_command *command)
{
	if (command->vars != NULL)
		free_var_array(command->vars);
	free(command);
	command = NULL;
}
