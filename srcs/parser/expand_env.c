/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expand_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:57 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:57 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	This function will replace $? by the current exit status of the shell.
*/

static int	replace_exit_status(t_shell *shell, char **vars, int i)
{
	char	*nbr;
	int		len;

	nbr = ft_itoa(shell->exit_status);
	if (nbr == NULL)
	{
		shell_error("Malloc failed");
		exit(1);
	}
	str_replace(vars, i, 2, nbr);
	len = ft_strlen(nbr);
	free(nbr);
	return (len);
}

/*
**	This function will loop through the command arguments
**	and delegate work to the helper functions.
*/

static void	exp_str_loop(t_shell *shell, t_expansion *exp, char **vars)
{
	int	i;

	i = 0;
	while ((*vars)[i])
	{
		exp_quote_handler(exp, (*vars)[i]);
		if ((*vars)[i] == '$' && exp->quote != SNGL_QUOTE &&
				exp->escape != ESCAPE)
		{
			if ((*vars)[i + 1] == '?')
				i += replace_exit_status(shell, vars, i);
			else if (is_env((*vars)[i + 1]))
				i += found_env(shell->env, vars, i);
			else
				++i;
			continue ;
		}
		if (exp->escape == ESCAPE && (*vars)[i] != '\\')
			exp->escape = NO_ESCAPE;
		++i;
	}
}

/*
**	The main function for the expander.
*/

void		expand_env(t_shell *shell, t_command *cmd)
{
	t_expansion	exp;
	char		**vars;

	vars = cmd->vars;
	while (*vars)
	{
		exp.quote = NO_QUOTE;
		exp.escape = NO_ESCAPE;
		exp_str_loop(shell, &exp, vars);
		++vars;
	}
}
