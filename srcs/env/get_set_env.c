/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_set_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:09 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:09 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will return the index of the environment variable
**	in the environment list.
*/

int			get_env_index(t_env *env, char *key)
{
	char	**pair;
	int		i;

	i = 0;
	while (env->vars[i])
	{
		pair = env_split(env->vars[i]);
		if (pair == NULL)
			shell_error_malloc();
		if (ft_strcmp(pair[0], key) == 0)
		{
			free_var_array(pair);
			break ;
		}
		free_var_array(pair);
		++i;
	}
	return (i);
}

/*
**	This function will return a string
**	containing the value of a key-value pair located on the heap.
*/

char		*get_env(t_env *env, char *key)
{
	char	**pair;
	char	*value;
	int		i;

	i = get_env_index(env, key);
	if (env->vars[i] == NULL)
	{
		value = ft_strdup("");
		if (value == NULL)
			shell_error_malloc();
		return (value);
	}
	pair = env_split(env->vars[i]);
	value = (pair[1]) ? ft_strdup(pair[1]) : ft_strdup("");
	if (value == NULL)
		shell_error_malloc();
	free_var_array(pair);
	return (value);
}

/*
**	This function will put a new environment variable
**	in the environment list.
*/

void		set_env(t_env *env, char *key, char *value)
{
	char	*tmp;
	int		i;

	i = get_env_index(env, key);
	if (env->vars[i] == NULL)
		resize_up_env(env, key);
	if (value)
	{
		free(env->vars[i]);
		tmp = ft_strjoin(key, "=");
		if (tmp == NULL)
			shell_error_malloc();
		env->vars[i] = ft_strjoin(tmp, value);
		free(tmp);
	}
	if (env->vars[i] == NULL)
		shell_error_malloc();
}
