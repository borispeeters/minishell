#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

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
	while (i < env->length)
	{
		env->vars[i] = ft_strdup(envp[i]);
		++i;
	}
	while (i < env->block_amount * env->block_size)
	{
		env->vars[i] = NULL;
		++i;
	}
	env->vars[i] = NULL;
}

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
	env->vars[prev_len] = new; // ft_strdup(new); ???
}

void	resize_down_env(t_env *env, int remove)
{
	char	**tmp;
	int		i;

	i = remove;
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
