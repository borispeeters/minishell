#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	execute(t_list *table, char **env)
{
	t_command	*command;
	char		**vars;
	pid_t		pid;
	char		*cmd;

	command = (t_command*)table->content;
	vars = command->vars;
	cmd = (ft_strchr(vars[0], '/') == NULL) ? search_path(vars[0], env) : ft_strdup(vars[0]);
	if (cmd == NULL)
	{
		write(2, "Something went wrong\n", 21);
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, vars, env);
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
	free(cmd);
}
