#include <string.h>
#include <sys/errno.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static void	cd_error(t_shell *shell, char **vars)
{
	char	*err_msg;

	write(2, "minishell: cd: ", 15);
	write(2, vars[1], ft_strlen(vars[1]));
	write(2, ": ", 2);
	err_msg = strerror(errno);
	write(2, err_msg, ft_strlen(err_msg));
	write(2, "\n", 1);
	shell->exit_status = 1;
	printf("YOMAN!\n");
}

void		update_pwd(t_env *env, char *key, char *value)
{
	char	*tmp;
	int		i;

	i = get_env(env, key);
	if (env->vars[i])
	{
		free(env->vars[i]);
		env->vars[i] = ft_strjoin(key, value);
		if (env->vars[i] == NULL)
			return ;
		free(value);
	}
	else
	{
		tmp = ft_strjoin(key, value);
		if (tmp == NULL)
			return ;
		resize_up_env(env, tmp);
	}
}

void		builtin_cd(t_shell *shell, t_env *env, char **vars)
{
	char	*prev_dir;
	char	*cur_dir;
	int		i;

	prev_dir = NULL;
	prev_dir = getcwd(prev_dir, 1);
	if (vars[1] && chdir(vars[1]) != 0)
		cd_error(shell, vars);
	else if (vars[1] == NULL)
	{
		i = get_env(env, "HOME");
		printf("[%s]\n", env->vars[i]);
		if (env->vars[i] == NULL)
		{
			printf("HOOOIOIII!!!!\n");
			write(2, "minishell: cd: HOME not set\n", 28);
			shell->exit_status = 1;
		}
		if (env->vars[i] && chdir(env->vars[i]) != 0)
			cd_error(shell, vars);
		printf("WHAAATA?!?!\n");
	}
	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, 1);
	update_pwd(env, "OLDPWD", prev_dir);
	update_pwd(env, "PWD", cur_dir);
}
