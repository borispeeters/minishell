#include "libft.h"
#include "minishell.h"

static void	str_replace(char **str, int index, int len, char *replace)
{
	char	*tmp;
	int		new_len;

	new_len = ft_strlen(*str) - len + ft_strlen(replace);
	tmp = malloc(sizeof(*tmp) * (new_len + 1));
	ft_strlcpy(tmp, *str, index + 1);
	ft_strlcat(tmp, replace, ft_strlen(tmp) + ft_strlen(replace) + 1);
	ft_strlcat(tmp, *str + index + len, new_len + 1);
	free(*str);
	*str = tmp;
}

static int	env_len(char *env)
{
	int	len;

	len = 1;
	if (!(ft_isalpha(env[len]) || env[len] == '_'))
	{
		++len;
		return (len);
	}
	while (env[len] && (ft_isalnum(env[len]) || env[len] == '_'))
	{
		++len;
	}
	return (len);
}

static void	free_pair(char **pair)
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

static char	*get_env_value(t_env *env, char *key)
{
	int		i;
	char	**pair;
	char	*value;

	i = 0;
	while (env->vars[i])
	{
		pair = ft_split(env->vars[i], '=');
		if (ft_strcmp(key, pair[0]) == 0)
		{
			free(key);
			free(pair[0]);
			value = pair[1];
			free(pair);
			return (value);
		}
		free_pair(pair);
		++i;
	}
	free(key);
	return (ft_strdup(""));
}

void	found_env(t_env *env, char **vars, int i)
{
	int		len;
	char	*value;

	len = env_len(*vars + i);
	value = get_env_value(env, ft_substr(*vars, i + 1, len - 1));
	str_replace(vars, i, len, value);
	i += ft_strlen(value);
	free(value);
}
