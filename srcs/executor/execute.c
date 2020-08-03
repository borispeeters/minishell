#include <sys/wait.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	execute(t_list *table, t_env *env)
{
	t_command	*command;
	char		**vars;
	pid_t		pid;
	char		*cmd;
	int			in_bak;
	int			out_bak;

	command = (t_command*)table->content;
	vars = command->vars;
	cmd = (ft_strchr(vars[0], '/') == NULL) ? search_path(vars[0], env->vars) : ft_strdup(vars[0]);
	if (cmd == NULL)
	{
		write(2, "minishell: command not found\n", 29);
		return ;
	}
	in_bak = dup(0);
	out_bak = dup(1);
	if (output_redir(command) != 0 || input_redir(command) != 0)
		return ;
	pid = fork();
	if (pid == 0)
	{
		execve(cmd, vars, env->vars);
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
	dup2(in_bak, 0);
	dup2(out_bak, 1);
	free(cmd);
}
