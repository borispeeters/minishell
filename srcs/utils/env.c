#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will free the environment list on exit of the shell.
*/

void	free_env(t_env *env)
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
**	This function will initiate the environent list on the heap
**	at startup of the shell.
*/

void	init_env(t_env *env, char **envp)
{
	int	i;

	env->block_size = 8;
	env->block_amount = 0;
	env->length = 0;
	i = 0;
	while (envp[env->length])
		++env->length;
	while (env->block_amount * env->block_size < env->length)
		++env->block_amount;
	env->vars = malloc(sizeof(*env->vars) * (env->block_amount * env->block_size + 1));
	if (env->vars == NULL)
		shell_error_malloc();
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
	while (i < env->block_amount * env->block_size)
	{
		env->vars[i] = NULL;
		++i;
	}
	env->vars[i] = NULL;
}

/*
**	This function will add a new environment variable to the environment list
**	and scale up the list if necessary.
*/

void	resize_up_env(t_env *env, char *new)
{
	char	**tmp;
	int		i;
	int		prev_len;

	prev_len = env->length;
	++env->length;
	if (env->length > env->block_amount * env->block_size)
	{
		++env->block_amount;
		tmp = malloc(sizeof(*tmp) * (env->block_amount * env->block_size + 1));
		if (tmp == NULL)
			shell_error_malloc();
		i = 0;
		while (i < prev_len)
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
	env->vars[prev_len] = ft_strdup(new);
}

/*
**	This function will remove an environment variable from the environment list
**	and scale down the list if necessary.
*/

void	resize_down_env(t_env *env, int i)
{
	char	**tmp;

	if (i == env->length)
		return ;
	--env->length;
	while (i < env->length)
	{
		env->vars[i] = env->vars[i + 1];
		++i;
	}
	env->vars[env->length] = NULL;
	if (env->length < (env->block_amount - 1) * env->block_size)
	{
		--env->block_amount;
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
}
