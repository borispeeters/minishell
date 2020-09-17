/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:21:32 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/17 10:51:57 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "minishell.h"

/*
**	Short helper function that tries to open a file, and prints an error it
**	it fails.
*/

static void	try_to_open(int *fd, char *file, int oflag, mode_t mode)
{
	*fd = open(file, oflag, mode);
	if (*fd == -1)
		shell_error_param(strerror(errno), file);
}

/*
**	This function will handle the call to dup2 for stdin or stdout.
*/

static int	duplicate_fd(int fd, int io)
{
	int	ret;

	ret = 0;
	if (fd != io)
	{
		if (dup2(fd, io) == -1)
		{
			shell_error(strerror(errno));
			ret = 1;
		}
		close(fd);
	}
	return (ret);
}

/*
**	This function will redirect the output from the standard output
**	to an output file.
*/

int			output_redir(t_command *cmd)
{
	int		oflag;
	char	*file;
	t_list	*tmp_files_out;
	t_list	*tmp_out_modes;

	cmd->fd_out = 1;
	tmp_files_out = cmd->files_out;
	tmp_out_modes = cmd->out_modes;
	while (tmp_files_out)
	{
		file = (char*)tmp_files_out->content;
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		if (*((t_filemode*)tmp_out_modes->content) == APPEND)
			oflag = O_APPEND;
		else if (*((t_filemode*)tmp_out_modes->content) == TRUNC)
			oflag = O_TRUNC;
		try_to_open(&cmd->fd_out, file, O_CREAT | oflag | O_WRONLY, 0644);
		if (cmd->fd_out == -1)
			return (1);
		tmp_files_out = tmp_files_out->next;
		tmp_out_modes = tmp_out_modes->next;
	}
	return (duplicate_fd(cmd->fd_out, 1));
}

/*
**	This function will redirect the input from the standard input
**	to an input file.
*/

int			input_redir(t_command *cmd)
{
	char	*file;
	t_list	*tmp_files_in;

	cmd->fd_in = 0;
	tmp_files_in = cmd->files_in;
	while (tmp_files_in)
	{
		file = (char*)tmp_files_in->content;
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		try_to_open(&cmd->fd_in, file, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
			return (1);
		tmp_files_in = tmp_files_in->next;
	}
	return (duplicate_fd(cmd->fd_in, 0));
}
