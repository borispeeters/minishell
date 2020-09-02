#include <unistd.h>
#include "minishell.h"

void	builtin_env(t_shell *shell, t_env *env, t_command *cmd)
{
	int	i;

	(void)shell;
	(void)cmd;
	i = 0;
	while (i < env->length)
	{
		if (ft_strchr(env->vars[i], '='))
			ft_putendl_fd(env->vars[i], STDOUT_FILENO);
		++i;
	}
}
