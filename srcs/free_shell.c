#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	free_shell(char **line, t_list **tokens)
{
	free(*line);
	*line = NULL;
	ft_lstclear(tokens, free_content);
}

void	free_command_table(t_list **table)
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
