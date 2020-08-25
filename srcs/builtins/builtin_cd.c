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
	set_env(env, "OLDPWD", prev_dir);
	free(prev_dir);
	set_env(env, "PWD", cur_dir);
	free(cur_dir);
}
