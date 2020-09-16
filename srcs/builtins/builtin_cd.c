/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_cd.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:20:28 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:33 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/errno.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	In case of an error, print it and set the exit status to 1
**	to indicate something went wrong.
*/

static void	cd_error(t_shell *shell, char *err_msg, char *param)
{
	shell->exit_status = 1;
	if (param)
		shell_error_builtin_param(err_msg, "cd", param);
	else
		shell_error_param(err_msg, "cd");
}

/*
**	Update the PWD and OLDPWD environment variables after changing directory.
*/

static void	update_pwd(t_shell *shell, char *oldpwd, char *pwd)
{
	if (ft_strcmp(oldpwd, pwd))
	{
		set_env(shell->env, "OLDPWD", oldpwd);
		set_env(shell->env, "PWD", pwd);
	}
}

/*
**	Change working directory to HOME.
*/

static void	go_home(t_shell *shell)
{
	char	*home;

	home = get_env(shell->env, "HOME");
	if (home == NULL)
		shell_error_malloc();
	if (!*home)
		cd_error(shell, "HOME not set", NULL);
	else if (chdir(home) != 0)
		cd_error(shell, strerror(errno), home);
	free(home);
}

/*
**	Change working directory to OLDPWD.
*/

static void	go_oldpwd(t_shell *shell)
{
	char	**pair;
	int		i;

	i = get_env_index(shell->env, "OLDPWD");
	if (shell->env->vars[i] == NULL)
	{
		cd_error(shell, "OLDPWD not set", NULL);
		return ;
	}
	pair = env_split(shell->env->vars[i]);
	if (pair[1] == NULL)
	{
		cd_error(shell, "OLDPWD not set", NULL);
		free_var_array(pair);
		return ;
	}
	if (chdir(pair[1]) != 0)
	{
		cd_error(shell, strerror(errno), pair[1]);
		free_var_array(pair);
		return ;
	}
	free_var_array(pair);
	builtin_pwd(shell);
}

/*
**	Builtin cd will change the working directory to the specified argument.
**	If not given, it will default to the HOME environment variable.
*/

void		builtin_cd(t_shell *shell)
{
	char	*oldpwd;
	char	*pwd;

	oldpwd = NULL;
	oldpwd = getcwd(oldpwd, 1);
	if (oldpwd == NULL)
		shell_error_malloc();
	if (shell->cmd->vars[1])
	{
		if (ft_strcmp(shell->cmd->vars[1], "-") == 0)
			go_oldpwd(shell);
		else if (chdir(shell->cmd->vars[1]) != 0)
			cd_error(shell, strerror(errno), shell->cmd->vars[1]);
	}
	else if (shell->cmd->vars[1] == NULL)
		go_home(shell);
	pwd = NULL;
	pwd = getcwd(pwd, 1);
	if (pwd == NULL)
		shell_error_malloc();
	update_pwd(shell, oldpwd, pwd);
	free(oldpwd);
	free(pwd);
}
