/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipes.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:30 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:21:30 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will redirect the standard input and standard output
**	to and from a pipe.
*/

static int	duplicate_pipe(int fd, int stream)
{
	int	ret;

	ret = 0;
	if (fd != stream)
	{
		if (dup2(fd, stream) == -1)
		{
			shell_error(strerror(errno));
			ret = 1;
		}
		close(fd);
	}
	return (ret);
}

/*
**	This function will setup a pipeline.
*/

int			handle_pipes(t_executor *exec, t_list *table)
{
	int	ret;

	ret = 0;
	exec->fd[READ_END] = STDIN_FILENO;
	exec->fd[WRITE_END] = STDOUT_FILENO;
	if (table->next && pipe(exec->fd) == -1)
	{
		shell_error(strerror(errno));
		return (1);
	}
	ret += duplicate_pipe(exec->in, STDIN_FILENO);
	ret += duplicate_pipe(exec->fd[WRITE_END], STDOUT_FILENO);
	return (ret);
}
