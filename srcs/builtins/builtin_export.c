/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:20:51 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:51 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will return a deep copy of the environment list.
*/

static char	**copy_env_list(t_env *env)
{
	int		i;
	char	**vars;

	vars = malloc_var_array(env->length);
	if (vars == NULL)
		shell_error_malloc();
	i = 0;
	while (env->vars[i])
	{
		vars[i] = ft_strdup(env->vars[i]);
		if (vars[i] == NULL)
		{
			free_var_array(vars);
			shell_error_malloc();
		}
		++i;
	}
	return (vars);
}

/*
**	Sort the entire list using the bubblesort algorithm.
*/

static char	**sort_env_list(t_env *env)
{
	int		i;
	int		j;
	char	**vars;
	char	*temp;

	vars = copy_env_list(env);
	i = 0;
	while (vars[i])
	{
		j = i + 1;
		while (vars[j])
		{
			if (ft_strcmp(vars[i], vars[j]) > 0)
			{
				temp = vars[i];
				vars[i] = vars[j];
				vars[j] = temp;
			}
			++j;
		}
		++i;
	}
	return (vars);
}

/*
**	Prints the value of an environment variable
**	with a backslash preceding double quotes and backslashes.
*/

static void	export_print_value(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\"' || s[i] == '\\')
			ft_putchar_fd('\\', STDOUT_FILENO);
		ft_putchar_fd(s[i], STDOUT_FILENO);
		++i;
	}
}

/*
**	This function will print the environment list in the correct format.
*/

static void	export_print(t_env *env)
{
	char	**vars;
	char	**pair;
	int		i;

	vars = sort_env_list(env);
	i = 0;
	while (vars[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		pair = env_split(vars[i]);
		ft_putstr_fd(pair[0], STDOUT_FILENO);
		if (pair[1])
		{
			ft_putstr_fd("=\"", STDOUT_FILENO);
			export_print_value(pair[1]);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
		free_var_array(pair);
		++i;
	}
	free_var_array(vars);
}

/*
**	Builtin export can set new variables in the environment list.
**	If no argument is given, display the entire list.
*/

void		builtin_export(t_shell *shell)
{
	char	**pair;
	int		i;

	i = 1;
	while (shell->cmd->vars[i])
	{
		pair = env_split(shell->cmd->vars[i]);
		if (valid_key(pair[0]))
			set_env(shell->env, pair[0], pair[1]);
		else
		{
			shell->exit_status = 1;
			shell_error_env(shell->cmd->vars[i], "export");
		}
		free_var_array(pair);
		++i;
	}
	if (i == 1)
		export_print(shell->env);
}
