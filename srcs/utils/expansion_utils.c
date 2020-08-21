#include "minishell.h"

int		is_env(int c)
{
	return (ft_isalnum(c) || c == '_');
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
	if (exp->escape != ESCAPE)
	{
		if (exp->quote == DBL_QUOTE)
			exp->quote = NO_QUOTE;
		else if (exp->quote == NO_QUOTE)
			exp->quote = DBL_QUOTE;
	}
}

void	exp_single_quote(t_expansion *exp)
{
	if (exp->quote == SNGL_QUOTE)
		exp->quote = NO_QUOTE;
	else if (exp->quote == NO_QUOTE && exp->escape != ESCAPE)
		exp->quote = SNGL_QUOTE;
}
