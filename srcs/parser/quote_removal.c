/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   quote_removal.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:03 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:04 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
**	This function will loop through the command arguments
**	and delegate work to other functions.
*/

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
		if (exp->escape == ESCAPE && (*vars)[i] != '\\' && tbc == 0)
			exp->escape = NO_ESCAPE;
		if (tbc == 0)
			++i;
	}
}

/*
**	The main function for the removal of quotes and the backslash character.
*/

void		quote_removal(t_command *cmd)
{
	t_expansion	exp;
	char		**vars;

	vars = cmd->vars;
	while (*vars)
	{
		exp.quote = NO_QUOTE;
		exp.escape = NO_ESCAPE;
		qr_str_loop(&exp, vars);
		++vars;
	}
}
