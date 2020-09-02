#include "minishell.h"

void	builtin_unset(t_shell *shell)
{
	int	i;

	i = 1;
	while (shell->cmd->vars[i])
	{
		if (valid_key(shell->cmd->vars[i]))
			resize_down_env(shell->env, get_env_index(shell->env, shell->cmd->vars[i]));
		else
			shell_error_env(shell->cmd->vars[i], "unset");
		++i;
	}
}
