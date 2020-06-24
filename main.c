/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 00:45:20 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/06/02 11:00:03 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <unistd.h>
#include <stdlib.h>

#include <limits.h>

void	free_line(char *line, char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
	free(line);
}

int		exec_prog(char **args)
{
	pid_t	pid;
	int		stat;

	pid = fork();
	if (pid == 0)
		execvp(args[0], args);
	else if (pid > 0)
		wait(&stat);
	else if (pid < 0)
		return (0);
	return (1);
}

int		exec_arg(char **args)
{
	if (ft_strncmp(args[0], "cd", 3) == 0)
	{
		if (args[1] == NULL)
			chdir("/Users/bpeeters"); // for now hardcoded; use environment variables
		else
			chdir(args[1]);
		return(1);
	}
	if (ft_strncmp(args[0], "exit", 5) == 0)
		return(0);
	return (exec_prog(args));
}

int		main(void)
{
	char	*line;
	char	**args;
	char	buf[PATH_MAX];
	char	*path;
	int		status;

	status = 1;
	while (status)
	{
		getcwd(buf, sizeof(buf));
		path = ft_strrchr(buf, '/') + 1;
		ft_printf("%s%% ", path);
		get_next_line(0, &line);
		args = ft_split(line, ' ');
		status = exec_arg(args);
		free_line(line, args);
	}
	return (0);
}
