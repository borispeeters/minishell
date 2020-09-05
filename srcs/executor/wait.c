#include <sys/wait.h>
#include "minishell.h"

/*
**	This function waits for the child process to finish
**	and receives its exit status.
*/

void			wait_cmd(t_shell *shell, t_executor *exec)
{
	int	status;

	waitpid(exec->pid, &status, WUNTRACED);
	if (WIFSIGNALED(status))
	{
		shell->sig = WTERMSIG(status);
		shell->exit_status = 128 + shell->sig;
	}
	if (WIFEXITED(status))
	{
		shell->exit_status = WEXITSTATUS(status);
	}
}
