#include "libft.h"
#include "minishell.h"

void	str_replace(char **str, int index, int len, char *replace)
{
	char	*tmp;
	int		new_len;

	new_len = ft_strlen(*str) - len + ft_strlen(replace);
	// printf("new_len: %d\n", new_len);
	tmp = malloc(sizeof(*tmp) * (new_len + 1));
	ft_strlcpy(tmp, *str, index + 1);
	// printf("after strlcpy: [%s]\n", tmp);
	ft_strlcat(tmp, replace, ft_strlen(tmp) + ft_strlen(replace) + 1);
	// printf("after strlcat: [%s]\n", tmp);
	ft_strlcat(tmp, *str + index + len, new_len + 1);
	// printf("after strlcat: [%s]\n", tmp);
	free(*str);
	*str = tmp;
}

int		env_len(char *env)
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

char	*get_env_value(t_env *env, char *key)
{
	int	i;

	i = 0;
	// printf("key: [%s]\n", key);
	while (env->vars[i])
	{
		// printf("env->vars[i]: [%s]\n", env->vars[i]);
		if (ft_strncmp(key, env->vars[i], ft_strlen(key)) == 0)
		{
			// printf("KAAASSS!!!\n");
			return (ft_strdup(env->vars[i] + ft_strlen(key) + 1));
		}
		++i;
	}
	return (ft_strdup(""));
}

void	expand_env(t_command *cmd, t_env *env)
{
	t_expansion	exp;
	char		**vars;
	int			i;
	int			len;
	char		*value;
	// char		*s = ft_strdup("hey $HOME $HOME");
	
	(void)env;
	vars = cmd->vars;
	// printf("pre-s: [%s]\n", s);
	// str_replace(&s, 10, 5, "/users/bpeeters");
	// printf("post-s: [%s]\n", s);
	// exit(0);
	while (*vars != NULL)
	{
		exp.quote = NO_QUOTE;
		exp.escape = NO_ESCAPE;
		exp.env = NULL;
		i = 0;
		while ((*vars)[i])
		{
			printf("%c\n", (*vars)[i]);
			if ((*vars)[i] == '\\')
			{
				if (exp.quote != SNGL_QUOTE)
				{
					if (exp.escape == NO_ESCAPE)
						exp.escape = ESCAPE;
					else if (exp.escape == ESCAPE)
						exp.escape = NO_ESCAPE;
				}
			}
			if ((*vars)[i] == '\"')
			{
				if (exp.quote == DBL_QUOTE)
					exp.quote = NO_QUOTE;
				else if (exp.quote == NO_QUOTE)
					exp.quote = DBL_QUOTE;
			}
			if ((*vars)[i] == '\'')
			{
				if (exp.quote == SNGL_QUOTE)
					exp.quote = NO_QUOTE;
				else if (exp.quote == NO_QUOTE)
					exp.quote = SNGL_QUOTE;
			}
			if ((*vars)[i] == '$' && exp.quote != SNGL_QUOTE && exp.escape != ESCAPE)
			{
				len = env_len(&((*vars)[i]));
				// // printf("env_len: %d\n", len);
				value = get_env_value(env, ft_substr(*vars, i + 1, len)) + 1;
				// printf("value: [%s]\n", value);
				str_replace(&(*vars), i, len, value);
				i += len + 1;
				continue ;
			}
			++i;
		}
		printf("*vars: [%s]\n", *vars);
		++vars;
	}
}
