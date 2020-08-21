#include "minishell.h"

static void	qr_str_loop(t_expansion *exp, char **vars)
{
	int i;
	int tbc;

	i = 0;
	while ((*vars)[i])
	{
		tbc = 0;
		if ((*vars)[i] == '\\')
			tbc += qr_escape(exp, vars, i);
		if ((*vars)[i] == '\"')
			tbc += qr_double_quote(exp, vars, i);
		if ((*vars)[i] == '\'')
			tbc += qr_single_quote(exp, vars, i);
		if (exp->escape == ESCAPE && (*vars)[i] != '\\')
			exp->escape = NO_ESCAPE;
		if (tbc == 0)
			++i;
	}
}

void		quote_removal(t_command *cmd)
{
	t_expansion	exp;
	char		**vars;

	vars = cmd->vars;
	while (*vars != NULL)
	{
		exp.quote = NO_QUOTE;
		exp.escape = NO_ESCAPE;
		qr_str_loop(&exp, vars);
		++vars;
	}
}
