#include "libft.h"
#include "minishell.h"

void	execute_loop(t_list *table, char **env)
{
	t_command	*command;
	char		**vars;

	(void)env;
	command = NULL;
	while (table != NULL)
	{
		command = (t_command*)table->content;
		vars = command->vars;
		while (*vars)
		{
			expand_env(vars, env);
			++vars;
		}
		while (command->files_in)
		{
			printf("%s\n", (char*)command->files_in->content);
			command->files_in = command->files_in->next;
		}
		while (command->files_out)
		{
			printf("%s\n", (char*)command->files_out->content);
			command->files_out = command->files_out->next;
		}
		table = table->next;
	}
}
