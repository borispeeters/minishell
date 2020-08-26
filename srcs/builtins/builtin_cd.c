#include <string.h>
#include <sys/errno.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

static void	cd_error(t_shell *shell, char *err_msg, char *param)
{
	shell_error_param(err_msg, param);
	shell->exit_status = 1;
}

static void	update_pwd(t_env *env, char *old_pwd, char *pwd)
{
	int	i;

	i = get_env_index(env, "OLDPWD");
	set_env(env, old_pwd, i);
	free(old_pwd);
	i = get_env_index(env, "PWD");
	set_env(env, pwd, i);
	free(pwd);
}

void		builtin_cd(t_shell *shell, t_env *env, char **vars)
{
	char	*prev_dir;
	char	*cur_dir;
	char	*home;

	prev_dir = NULL;
	prev_dir = getcwd(prev_dir, 1);
	if (vars[1] && chdir(vars[1]) != 0)
		cd_error(shell, strerror(errno), "cd");
	else if (vars[1] == NULL)
	{
		home = get_env(env, "HOME");
		if (!*home)
			cd_error(shell, "HOME not set", "cd");
		else if (chdir(home) != 0)
			cd_error(shell, strerror(errno), "cd");
		free(home);
	}
	cur_dir = NULL;
	cur_dir = getcwd(cur_dir, 1);
	update_pwd(env, prev_dir, cur_dir);	
}
