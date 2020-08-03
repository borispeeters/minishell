#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

void	init_env(t_env *env, char **envp)
{
	int	 i;

	env->block_size = 5;
	env->block_amount = 0;
	env->length = 0;
	i = 0;
	while (envp[env->length])
		++env->length;
	while (env->block_amount * env->block_size < env->length)
		++env->block_amount;
	env->vars = malloc(sizeof(*env->vars) * (env->block_amount * env->block_size));
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
}

void	free_env(t_env *env)
{
	int i;

	i = 0;
	while (i < env->length)
	{
		// printf("%s\n", env->vars[i]);
		free(env->vars[i]);
		env->vars[i] = NULL;
		++i;
	}
	// free(env->vars);
	// env->vars = NULL;
}

void	resize_up_env(t_env *env, char *new)
{
	char	**tmp;
	int		i;
	int		prev_len;

	prev_len = env->length;
	++env->length;
	if (env->length > (env->block_amount + 1) * env->block_size)
	{
		++env->block_amount;
		tmp = malloc(sizeof(*tmp) * (env->block_amount * env->block_size));
		i = 0;
		while (i < prev_len)
		{
			tmp[i] = env->vars[i];
			++i;
		}
		while (i < env->block_amount * env->block_size)
		{
			tmp[i] = NULL;
			printf("TMP: %s\n", tmp[i]);
			++i;
		}
		free(env->vars);
		env->vars = tmp;
	}
	printf("NEW: %s\n", env->vars[prev_len]);
	env->vars[prev_len] = new; // ft_strdup(new); ???
}

void	resize_down_env(t_env *env, char *remove)
{
	char	**tmp;
	int		i;

	i = 0;
	--env->length;
	while (i <= env->length)
	{
		if (ft_strcmp(env->vars[i], remove) == 0)
		{
			free(env->vars[i]);
			env->vars[i] = env->vars[env->length];
		}
		++i;
	}
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
		free(env->vars);
		env->vars = tmp;
	}
}
