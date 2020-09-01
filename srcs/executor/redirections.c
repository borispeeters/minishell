#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> // maybe verwijder? is voor strerror
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
			return (-1);
		tmp_files_out = tmp_files_out->next;
		tmp_out_modes = tmp_out_modes->next;
	}
	dup2(cmd->fd_out, 1);
	return (0);
}

int			input_redir(t_command *cmd)
{
	char	*file;

	cmd->fd_in = 0;
	while (cmd->files_in)
	{
		file = (char*)cmd->files_in->content;
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		try_to_open(&cmd->fd_in, file, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
			return (-1);
		cmd->files_in = cmd->files_in->next;
	}
	dup2(cmd->fd_in, 0);
	return (0);
}
