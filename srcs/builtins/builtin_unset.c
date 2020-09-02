#include "minishell.h"

void	builtin_unset(t_shell *shell, t_env *env, t_command *cmd)
{
	int	i;

	(void)shell;
	i = 1;
	while (cmd->vars[i])
	{
		if (valid_key(cmd->vars[i]))
			resize_down_env(env, get_env_index(env, cmd->vars[i]));
		else
			shell_error_env(cmd->vars[i], "unset");
		++i;
	}
}
