#include <unistd.h>
#include "minishell.h"

void	builtin_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->length)
	{
		if (ft_strchr(env->vars[i], '='))
		{
			write(1, env->vars[i], ft_strlen(env->vars[i]));
			write(1, "\n", 1);
		}
		++i;
	}
}
