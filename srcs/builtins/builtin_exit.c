#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_exit(t_shell *shell, t_env *env, t_command *cmd)
{
	(void)env;
	if (cmd->vars[2] != NULL)
	{
		shell_error_param("too many arguments", "exit");
		shell->exit_status = 1;
		return ;
	}
	if (cmd->vars[1])
		shell->exit_status = ft_atoi(cmd->vars[1]);
	shell->status = 0;
}
