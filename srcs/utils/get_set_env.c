#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void		free_pair(char **pair)
{
	int	i;

	i = 0;
	while (pair[i])
	{
		free(pair[i]);
		++i;
	}
	free(pair);
}

int			get_env(t_env *env, char *var)
{
	char	**pair;
	int		i;

	i = 0;
	while (env->vars[i])
	{
		pair = ft_split(env->vars[i], '=');
		if (ft_strcmp(pair[0], var) == 0)
		{
			free_pair(pair);
			break ;
		}
		free_pair(pair);
		++i;
	}
	return (i);
}

void		set_env(t_env *env, char *value, int i)
{
	if (env->vars[i] == NULL)
		resize_up_env(env, value);
}
