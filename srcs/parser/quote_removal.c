#include "minishell.h"

void	remove_character(char **str, int i)
{
	char	*tmp;

	tmp = malloc(sizeof(*tmp) * ft_strlen(*str));
	ft_strlcpy(tmp, *str, i + 1);
	// printf("after strlcpy: %s\n", tmp);
	// printf("str + i + 1: %s\nlen: %zu\n", *str + i + 1, ft_strlen(*str));
	ft_strlcat(tmp, *str + i + 1, ft_strlen(*str));
	// printf("after strlcat: %s\n", tmp);
	free(*str);
	*str = tmp;
}

void	quote_removal(t_command *cmd)
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
			printf("%c\n", (*vars)[i]);
			if ((*vars)[i] == '\\')
			{
				exp_escape_char(&exp);
				if (exp.quote != SNGL_QUOTE && exp.escape == ESCAPE)
				{
					remove_character(vars, i);
					continue ;
				} 
			}
			if ((*vars)[i] == '\"')
			{
				exp_double_quote(&exp);
				if (exp.quote != SNGL_QUOTE && exp.escape != ESCAPE)
				{
					remove_character(vars, i);
					continue ;
				}
			}
			if ((*vars)[i] == '\'')
			{
				exp_single_quote(&exp);
				if (exp.quote != DBL_QUOTE && exp.escape != ESCAPE)
				{
					printf("HEYHEY\n");
					remove_character(vars, i);
					continue ;
				}
			}
			if (exp.escape == ESCAPE && (*vars)[i] != '\\')
			{
				exp.escape = NO_ESCAPE;
				printf("OUT OF ESCAPE\n");
			}
			++i;
			printf("*vars: [%s]\n", *vars);
		}
		++vars;
	}
}