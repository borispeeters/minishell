/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   resize_env.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:16 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:17 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
**	This function will handle the allocation for the bigger environment list.
*/

static void	realloc_up(t_env *env)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(*tmp) * (env->block_amount * env->block_size + 1));
	if (tmp == NULL)
		shell_error_malloc();
	i = 0;
	while (i < env->length - 1)
	{
		tmp[i] = env->vars[i];
		++i;
	}
	while (i < env->block_amount * env->block_size)
	{
		tmp[i] = NULL;
		++i;
	}
	tmp[i] = NULL;
	free(env->vars);
	env->vars = tmp;
}

/*
**	This function will add a new environment variable to the environment list
**	and scale up the list if necessary.
*/

void		resize_up_env(t_env *env, char *new)
{
	++env->length;
	if (env->length > env->block_amount * env->block_size)
	{
		++env->block_amount;
		realloc_up(env);
	}
	env->vars[env->length - 1] = ft_strdup(new);
}

/*
**	This function will handle the allocation for the smaller environment list.
*/

static void	realloc_down(t_env *env)
{
	char	**tmp;
	int		i;

	tmp = malloc(sizeof(*tmp) * (env->block_amount * env->block_size));
	if (tmp == NULL)
		shell_error_malloc();
	i = 0;
	while (i < env->length)
	{
		tmp[i] = env->vars[i];
		++i;
	}
	tmp[i] = NULL;
	free(env->vars);
	env->vars = tmp;
}

/*
**	This function will remove an environment variable from the environment list
**	and scale down the list if necessary.
*/

void		resize_down_env(t_env *env, int remove)
{
	if (remove == env->length)
		return ;
	free(env->vars[remove]);
	--env->length;
	while (remove < env->length)
	{
		env->vars[remove] = env->vars[remove + 1];
		++remove;
	}
	env->vars[env->length] = NULL;
	if (env->length < (env->block_amount - 1) * env->block_size)
	{
		--env->block_amount;
		realloc_down(env);
	}
}
