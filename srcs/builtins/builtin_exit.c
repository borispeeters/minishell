#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_exit(t_shell *shell)
{
	if (shell->cmd->vars[2] != NULL)
	{
		shell_error_param("too many arguments", "exit");
		shell->exit_status = 1;
		return ;
	}
	if (shell->cmd->vars[1])
		shell->exit_status = ft_atoi(shell->cmd->vars[1]);
	shell->status = 0;
}
