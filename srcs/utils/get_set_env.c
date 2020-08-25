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

int			get_env_index(t_env *env, char *key)
{
	char	**pair;
	int		i;

	i = 0;
	while (env->vars[i])
	{
		pair = ft_split(env->vars[i], '=');
		if (ft_strcmp(pair[0], key) == 0)
		{
			free_pair(pair);
			break ;
		}
		free_pair(pair);
		++i;
	}
	return (i);
}

char		*get_env(t_env *env, char *key)
{
	char	**pair;
	char	*value;
	int		i;

	i = get_env_index(env, key);
	if (env->vars[i] == NULL)
		return (ft_strdup(""));
	pair = ft_split(env->vars[i], '=');
	value = (pair[1]) ? ft_strdup(pair[1]) : ft_strdup("");
	free_pair(pair);
	return (value);
}

void		set_env(t_env *env, char *key, char *value)
{
	char	**pair;
	char	*tmp;
	int		i;

	i = get_env_index(env, key);
	if (env->vars[i] == NULL)
		resize_up_env(env, key);
	pair = ft_split(env->vars[i], '=');
	free(env->vars[i]);
	tmp = ft_strjoin(pair[0], "=");
	env->vars[i] = ft_strjoin(tmp, value);
	free(tmp);
}
