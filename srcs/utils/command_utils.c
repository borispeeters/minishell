#include "minishell.h"
#include "libft.h"

/*
**	This function will malloc a command structure, and the vars array in it.
*/
t_list		*prepare_command(int length)
{
	t_list		*link;
	t_command	*command;

	if (length <= 0)
		return (NULL);
	command = malloc(sizeof(t_command));
	if (command == NULL)
		return (NULL);
	link = ft_lstnew(command);
	if (link == NULL)
	{
		free(command);
		return (NULL);
	}
	command->vars = malloc_var_array(length + 1);
	if (command->vars == NULL)
	{
		free_command(command);
		return (NULL);
	}
	command->files_in = NULL;
	command->files_out = NULL;
	command->out_modes = NULL;
	command->pipe = PIPE_NONE;
	return (link);
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
