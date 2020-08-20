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

int		is_env(int c)
{
	return (ft_isalnum(c) || c == '_');
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
	int	len;

	i = 0;
	while (env->vars[i])
	{
		if (ft_strncmp(key, env->vars[i], ft_strlen(key)) == 0)
		{
			len = ft_strlen(key);
			free(key);
			return (ft_strdup(env->vars[i] + len + 1));
		}
		++i;
	}
	free(key);
	return (ft_strdup(""));
}

void	exp_escape_char(t_expansion *exp)
{
	if (exp->quote != SNGL_QUOTE)
	{
		if (exp->escape == NO_ESCAPE)
			exp->escape = ESCAPE;
		else if (exp->escape == ESCAPE)
			exp->escape = NO_ESCAPE;
	}
}

void	exp_double_quote(t_expansion *exp)
{
	if (exp->quote == DBL_QUOTE)
		exp->quote = NO_QUOTE;
	else if (exp->quote == NO_QUOTE)
		exp->quote = DBL_QUOTE;
}

void	exp_single_quote(t_expansion *exp)
{
	if (exp->quote == SNGL_QUOTE)
		exp->quote = NO_QUOTE;
	else if (exp->quote == NO_QUOTE)
		exp->quote = SNGL_QUOTE;
}

void	found_env(t_env *env, char **vars, int i)
{
	int		len;
	char	*value;

	len = env_len(*vars + i);
	printf("env_len: %d\n", len);
	value = get_env_value(env, ft_substr(*vars, i + 1, len - 1));
	printf("value: [%s]\n", value);
	str_replace(vars, i, len, value);
	i += ft_strlen(value);
	free(value);
}

void	expand_env(t_command *cmd, t_env *env)
{
	t_expansion	exp;
	char		**vars;
	int			i;
	
	vars = cmd->vars;
	while (*vars != NULL)
	{
		exp.quote = NO_QUOTE;
		exp.escape = NO_ESCAPE;
		i = 0;
		while ((*vars)[i])
		{
			if ((*vars)[i] == '\\')
				exp_escape_char(&exp);
			if ((*vars)[i] == '\"')
				exp_double_quote(&exp);
			if ((*vars)[i] == '\'')
				exp_single_quote(&exp);
			if ((*vars)[i] == '$' && exp.quote != SNGL_QUOTE && exp.escape != ESCAPE && is_env((*vars)[i + 1]))
			{
				found_env(env, vars, i);
				continue ;
			}
			if (exp.escape == ESCAPE && (*vars)[i] != '\\')
				exp.escape = NO_ESCAPE;
			++i;
		}
		// printf("*vars: [%s]\n", *vars);
		++vars;
	}
}
