#include "libft.h"
#include "minishell.h"

int		count_occurrences(char *str, char *s1)
{
	int	count;

	count = 0;
	str = ft_strnstr(str, s1, ft_strlen(str));
	while (str && *str)
	{
		str += ft_strlen(s1);
		str = ft_strnstr(str, s1, ft_strlen(str));
		++count;
	}
	return (count);
}

void	str_replace(char **str, char *s1, char *s2)
{
	int		length;
	int		count;
	char	*tmp;
	char	*segment_begin;
	char	*segment_end;

	count = count_occurrences(*str, s1);
	// printf("count: %d\n", count);
	length = ft_strlen(*str);
	// printf("pre-length: %d\n", length);
	length += count * (ft_strlen(s2) - ft_strlen(s1));
	// printf("post-length: %d\n", length);
	tmp = malloc(sizeof(*tmp) * (length + 1));
	segment_begin = *str;
	segment_end = ft_strnstr(*str, s1, ft_strlen(*str));
	while (1)
	{
		ft_strlcpy(tmp, segment_begin, segment_end - segment_begin + 1);
		printf("after strlcpy: [%s]\n", tmp);
		ft_strlcat(tmp, s2, ft_strlen(tmp) + ft_strlen(s2) + 1);
		printf("after strlcat: [%s]\n", tmp);
		segment_begin += ft_strlen(s1);
		segment_begin = ft_strnstr(segment_begin, s1, ft_strlen(*str));
	}
}

void	expand_env(t_command *cmd, t_env *env)
{
	t_expansion	exp;
	int			isenv;
	char		**vars;
	char		*str;
	char		*s = ft_strdup("hallo kinderen roerei nog een kind");
	
	(void)env;
	vars = cmd->vars;
	printf("pre-s: [%s]\n", s);
	str_replace(&s, "kind", "stront");
	printf("post-s: [%s]\n", s);
	exit(0);
	while (*vars != NULL)
	{
		exp.quote = NO_QUOTE;
		isenv = 0;
		exp.env = NULL;
		str = *vars;
		while (*str)
		{
			if (*str == '\"')
			{
				if (exp.quote == DBL_QUOTE)
				{
					exp.quote = NO_QUOTE;
					if (isenv)
					{
						isenv = 0;
						exp.env = ft_substr(exp.env_start, 0, exp.env_len);
					}
				}
				else if (exp.quote == NO_QUOTE)
					exp.quote = DBL_QUOTE;
			}
			if (*str == '\'')
			{
				if (exp.quote == SNGL_QUOTE)
				{
					exp.quote = NO_QUOTE;
					if (isenv)
					{
						isenv = 0;
						exp.env = ft_substr(exp.env_start, 0, exp.env_len);
					}
				}
				else if (exp.quote == NO_QUOTE)
					exp.quote = SNGL_QUOTE;
			}
			if (*str == '$' && exp.quote != SNGL_QUOTE)
			{
				isenv = 1;
				exp.env_start = str;
				exp.env_len = 0;
			}
			else if (!ft_isalnum(*str) && isenv == 1)
			{
				isenv = 0;
				exp.env = ft_substr(exp.env_start, 0, exp.env_len);
			}
			if (isenv)
				++exp.env_len;
			++str;
		}
		++vars;
		if (isenv)
		{
			isenv = 0;
			exp.env = ft_substr(exp.env_start, 0, exp.env_len);
		}
		printf("env: %s\n", exp.env);
	}
}
