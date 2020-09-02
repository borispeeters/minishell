#include <unistd.h>
#include "minishell.h"

void	builtin_env(t_shell *shell)
{
	int	i;

	i = 0;
	while (i < shell->env->length)
	{
		if (ft_strchr(shell->env->vars[i], '='))
			ft_putendl_fd(shell->env->vars[i], STDOUT_FILENO);
		++i;
	}
}
