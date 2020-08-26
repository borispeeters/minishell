#include "libft.h"
#include "minishell.h"

static int	double_quoted_backslash(int c)
{
	return (c == '\"' || c == '\\' || c == '$' || c == '\n');
}

static void	remove_character(char **str, int i)
{
	char	*tmp;

	tmp = malloc(sizeof(*tmp) * ft_strlen(*str));
	ft_strlcpy(tmp, *str, i + 1);
	ft_strlcat(tmp, *str + i + 1, ft_strlen(*str));
	free(*str);
	*str = tmp;
}

int			qr_single_quote(t_expansion *exp, char **vars, int i)
{
	exp_single_quote(exp);
	if (exp->quote != DBL_QUOTE && exp->escape != ESCAPE)
	{
		remove_character(vars, i);
		return (1);
	}
	return (0);
}

int			qr_double_quote(t_expansion *exp, char **vars, int i)
{
	exp_double_quote(exp);
	if (exp->quote != SNGL_QUOTE && exp->escape != ESCAPE)
	{
		remove_character(vars, i);
		return (1);
	}
	return (0);
}

int			qr_escape(t_expansion *exp, char **vars, int i)
{
	exp_escape_char(exp);
	if (exp->escape == ESCAPE)
	{
		if ((exp->quote == DBL_QUOTE &&
		double_quoted_backslash((*vars)[i + 1])) || exp->quote == NO_QUOTE)
		{
			remove_character(vars, i);
			return (1);
		}
	}
	return (0);
}