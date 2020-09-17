/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   command_utils.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:19 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/17 11:33:02 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	This function will free a command struct and its variables.
*/

static void	free_command(t_command *command)
{
	if (command->vars != NULL)
		free_var_array(command->vars);
	free(command);
	command = NULL;
}

/*
**	This function will malloc a command structure, and the vars array in it.
*/

t_list		*prepare_command(int length)
{
	t_list		*link;
	t_command	*command;

	command = malloc(sizeof(t_command));
	if (command == NULL)
		shell_error_malloc();
	link = ft_lstnew(command);
	if (link == NULL)
	{
		free(command);
		shell_error_malloc();
	}
	command->vars = malloc_var_array(length);
	if (command->vars == NULL)
	{
		free_command(command);
		shell_error_malloc();
	}
	command->files_in = NULL;
	command->files_out = NULL;
	command->out_modes = NULL;
	command->pipe = PIPE_NONE;
	return (link);
}

/*
**	Frees the memory used by the command table.
*/

void		free_command_table(t_list **table)
{
	t_list		*node;
	t_command	*cmd;

	node = *table;
	while (node)
	{
		cmd = node->content;
		ft_lstclear(&cmd->files_in, free_content);
		ft_lstclear(&cmd->files_out, free_content);
		ft_lstclear(&cmd->out_modes, free_content);
		free_var_array(cmd->vars);
		node = node->next;
	}
	ft_lstclear(table, free_content);
}
