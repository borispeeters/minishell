/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_env.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:13 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:14 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will free the environment list on exit of the shell.
*/

void		free_env(t_env *env)
{
	int i;

	i = 0;
	while (i < env->length)
	{
		free(env->vars[i]);
		env->vars[i] = NULL;
		++i;
	}
	free(env->vars);
	env->vars = NULL;
}

/*
**	This function will allocate memory to store a copy of the original envp
**	on the heap, so it can be modified later.
*/

static void	allocate_env_list(t_env *env, char **envp, int space)
{
	int	i;

	env->vars = malloc(sizeof(*env->vars) * (space + 1));
	if (env->vars == NULL)
		shell_error_malloc();
	i = 0;
	while (i < env->length)
	{
		env->vars[i] = ft_strdup(envp[i]);
		if (env->vars[i] == NULL)
		{
			env->length = i;
			free_env(env);
			shell_error_malloc();
		}
		++i;
	}
	while (i < space)
	{
		env->vars[i] = NULL;
		++i;
	}
	env->vars[i] = NULL;
}

/*
**	This function will initiate the environent list on the heap
**	at startup of the shell.
*/

void		init_env(t_env *env, char **envp)
{
	env->block_size = 8;
	env->block_amount = 0;
	env->length = 0;
	while (envp[env->length])
		++env->length;
	while (env->block_amount * env->block_size < env->length)
		++env->block_amount;
	allocate_env_list(env, envp, env->block_amount * env->block_size);
}
