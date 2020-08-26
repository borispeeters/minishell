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

void	found_env(t_env *env, char **vars, int i)
{
	int		len;
	char	*value;

	len = env_len(*vars + i);
	value = get_env(env, ft_substr(*vars, i + 1, len - 1));
	str_replace(vars, i, len, value);
	i += ft_strlen(value);
	free(value);
}
