#include "minishell.h"

void	builtin_unset(t_env *env, char **vars)
{
	int		i;

	i = 1;
	while (vars[i])
	{
		if (valid_key(vars[i]))
			resize_down_env(env, get_env_index(env, vars[i]));
		else
			shell_error_env(vars[i], "unset");
		++i;
	}
}
