#include <stdlib.h>
#include <sys/stat.h>
#include "libft.h"
#include "minishell.h"

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

static char	*make_abs_path(t_path *path, int i, char *cmd)
{
	char	*tmp;

	tmp = ft_strjoin(path->path_dirs[i], "/");
	if (tmp == NULL)
	{
		free_path(path);
		return (NULL);
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
		return (NULL);
	}
	return (path->abs);
}

static char	*search_path_dirs(t_path *path, char *cmd)
{
	struct stat	buf;
	char		*ret;
	int			i;

	i = 0;
	while (path->path_dirs[i])
	{
		if (make_abs_path(path, i, cmd) == NULL)
		{
			free_path(path);
			return (NULL);
		}
		stat(path->abs, &buf);
		if (S_ISREG(buf.st_mode))
		{
			ret = ft_strdup(path->abs);
			free_path(path);
			return (ret);
		}
		++i;
	}
	free_path(path);
	return (NULL);
}

static char	*found_path(t_path *path, char **env, char *cmd)
{
	path->path = ft_substr(*env, 5, ft_strlen(*env) - 5);
	if (path->path == NULL)
		return (NULL);
	path->path_dirs = ft_split(path->path, ':');
	if (path->path_dirs == NULL)
	{
		free_path(path);
		return (NULL);
	}
	return (search_path_dirs(path, cmd));
}

char	*search_path(char *cmd, char **env)
{
	t_path	path;

	path.path = NULL;
	path.path_dirs = NULL;
	path.abs = NULL;
	while (*env)
	{
		if (ft_strncmp(*env, "PATH=", 5) == 0)
			return (found_path(&path, env, cmd));
		++env;
	}
	return (ft_strdup(cmd));
}
