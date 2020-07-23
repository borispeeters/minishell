#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	execute(t_list *table, char **env)
{
	t_command	*command;
	char		**vars;
	pid_t		pid;

	command = (t_command*)table->content;
	vars = command->vars;
	pid = fork();
	if (pid == 0)
	{
		execve(vars[0], vars, env);
		exit(1);
	}
	else if (pid > 0)
	{
		wait(NULL);
	}
	else if (pid < 0)
	{
		write(2, "minishell: failed to fork child process\n", 40);
	}
}
