/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   search_path.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:35 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:35 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "minishell.h"

/*
**	A utility function to free memory used for PATH traversal.
*/

static void	free_path(t_path *path)
{
	int	i;

	free(path->path);
	path->path = NULL;
	free(path->abs);
	path->abs = NULL;
	i = 0;
	while (path->path_dirs && path->path_dirs[i])
	{
		free(path->path_dirs[i]);
		path->path_dirs[i] = NULL;
		++i;
	}
	free(path->path_dirs);
	path->path_dirs = NULL;
}

/*
**	This function will create an absolute path from a command.
*/

static void	make_abs_path(t_path *path, int i, char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(path->path_dirs[i], "/");
	if (tmp == NULL)
	{
		free_path(path);
		shell_error_malloc();
	}
	if (path->abs)
	{
		free(path->abs);
		path->abs = NULL;
	}
	path->abs = ft_strjoin(tmp, cmd);
	free(tmp);
	if (path->abs == NULL)
	{
		free_path(path);
		shell_error_malloc();
	}
}

/*
**	This function will search for an existing executable
**	in the directories in the PATH environment variable,
**	going from left to right.
*/

static char	*search_path_dirs(t_path *path, char *cmd)
{
	struct stat	buf;
	char		*ret;
	int			i;

	i = 0;
	while (path->path_dirs[i])
	{
		make_abs_path(path, i, cmd);
		stat(path->abs, &buf);
		if (S_ISREG(buf.st_mode))
		{
			ret = ft_strdup(path->abs);
			free_path(path);
			if (ret == NULL)
				shell_error_malloc();
			return (ret);
		}
		++i;
	}
	free_path(path);
	return (NULL);
}

/*
**	This function will get all the individual paths
**	in the PATH environment variable.
*/

static char	*found_path(t_path *path, char **env, char *cmd)
{
	path->path = ft_substr(*env, 5, ft_strlen(*env) - 5);
	if (path->path == NULL)
		return (NULL);
	path->path_dirs = ft_split(path->path, ':');
	if (path->path_dirs == NULL)
	{
		free_path(path);
		shell_error_malloc();
	}
	return (search_path_dirs(path, cmd));
}

/*
**	This function will search for the PATH environment variable
**	and if it can't be found return the original command.
*/

char		*search_path(char *cmd, char **env)
{
	t_path	path;
	char	*ret;

	path.path = NULL;
	path.path_dirs = NULL;
	path.abs = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (found_path(&path, env, cmd));
		++env;
	}
	ret = ft_strdup(cmd);
	if (ret == NULL)
		shell_error_malloc();
	return (ret);
}
