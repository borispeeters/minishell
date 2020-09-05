#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

/*
**	This function will replace a subsection of str with replace.
*/

void		str_replace(char **str, int index, int len, char *replace)
{
	char	*tmp;
	int		new_len;

	new_len = ft_strlen(*str) - len + ft_strlen(replace);
	tmp = malloc(sizeof(*tmp) * (new_len + 1));
	if (tmp == NULL)
		shell_error_malloc();
	ft_strlcpy(tmp, *str, index + 1);
	ft_strlcat(tmp, replace, ft_strlen(tmp) + ft_strlen(replace) + 1);
	ft_strlcat(tmp, *str + index + len, new_len + 1);
	free(*str);
	*str = tmp;
}

/*
**	This function will return the length of an environment variable
**	before it is expanded.
*/

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

/*
**	This function will replace an environment variable when it is found.
*/

int			found_env(t_env *env, char **vars, int i)
{
	int		len;
	char	*value;
	char	*key;

	len = env_len(*vars + i);
	key = ft_substr(*vars, i + 1, len - 1);
	if (key == NULL)
		shell_error_malloc();
	value = get_env(env, key);
	free(key);
	if (value == NULL)
		shell_error_malloc();
	str_replace(vars, i, len, value);
	len = ft_strlen(value);
	free(value);
	return (len);
}
