#include "libft.h"
#include "minishell.h"

char	**copy_env_list(t_env *env)
{
	int		i;
	char	**vars;

	vars = malloc_var_array(env->length);
	i = 0;
	while (env->vars[i])
	{
		vars[i] = ft_strdup(env->vars[i]);
		++i;
	}
	return (vars);
}

char	**sort_env_list(t_env *env)
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

void	export_print(t_env *env)
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
			ft_putstr_fd(pair[1], STDOUT_FILENO);
			ft_putstr_fd("\"", STDOUT_FILENO);
		}
		ft_putstr_fd("\n", STDOUT_FILENO);
		free_var_array(pair);
		++i;
	}
	free_var_array(vars);
}

void	builtin_export(t_shell *shell)
{
	char	**pair;
	int		i;

	i = 1;
	while (shell->cmd->vars[i])
	{
		pair = env_split(shell->cmd->vars[i]);
		if (pair == NULL)
			shell_error_malloc();
		if (valid_key(pair[0]))
			set_env(shell->env, pair[0], pair[1]);
		else
			shell_error_env(shell->cmd->vars[i], "export");
		free_var_array(pair);
		++i;
	}
	if (i == 1)
		export_print(shell->env);
}
