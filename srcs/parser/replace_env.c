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

static char	*get_env_value(t_env *env, char *key)
{
	int		i;
	char	**pair;
	char	*value;

	value = NULL;
	i = get_env(env, key);
	if (env->vars[i] == NULL)
		return (ft_strdup(""));
	pair = ft_split(env->vars[i], '=');
	value = (pair[1]) ? ft_strdup(pair[1]) : ft_strdup("");
	free_pair(pair);
	return (value);
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
