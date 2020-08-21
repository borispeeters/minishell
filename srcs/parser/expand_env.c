#include "libft.h"
#include "minishell.h"

static void	exp_str_loop(t_env *env, t_expansion *exp, char **vars)
{
	int	i;

	i = 0;
	while ((*vars)[i])
	{
		if ((*vars)[i] == '\\')
			exp_escape_char(exp);
		if ((*vars)[i] == '\"')
			exp_double_quote(exp);
		if ((*vars)[i] == '\'')
			exp_single_quote(exp);
		if ((*vars)[i] == '$' && exp->quote != SNGL_QUOTE &&
		exp->escape != ESCAPE && is_env((*vars)[i + 1]))
		{
			found_env(env, vars, i);
			continue ;
		}
		if (exp->escape == ESCAPE && (*vars)[i] != '\\')
			exp->escape = NO_ESCAPE;
		++i;
	}
}

void		expand_env(t_command *cmd, t_env *env)
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
		exp_str_loop(env, &exp, vars);
		// printf("*vars: [%s]\n", *vars);
		++vars;
	}
}
