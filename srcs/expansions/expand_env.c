#include "minishell.h"

void	expand_env(char **str, char **env)
{
	t_expansion	exp;
	int			isenv;
	
	(void)env;
	exp.quote = NO_QUOTE;
	isenv = 0;
	exp.env = NULL;
	while (**str)
	{
		if (**str == '\"')
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
		if (**str == '\'')
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
		if (**str == '$' && exp.quote != SNGL_QUOTE)
		{
			isenv = 1;
			exp.env_start = *str;
			exp.env_len = 0;
		}
		else if (!ft_isalnum(**str) && isenv == 1)
		{
			isenv = 0;
			exp.env = ft_substr(exp.env_start, 0, exp.env_len);
		}
		if (isenv)
			++exp.env_len;
		++(*str);
	}
	printf("env: %s\n", exp.env);
}
