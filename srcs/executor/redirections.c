#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"

static void	check_dir(char *name)
{
	struct stat	buf;

	stat(name, &buf);
	if (S_ISDIR(buf.st_mode))
		shell_error_param("Is a directory", name);
}

int			output_redir(t_command *cmd)
{
	int		oflag;
	char	*file;

	cmd->fd_out = 1;
	while (cmd->files_out)
	{
		file = (char*)cmd->files_out->content;
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		check_dir(file);
		if ((t_filemode)cmd->out_modes->content == APPEND)
			oflag = O_APPEND;
		else if ((t_filemode)cmd->out_modes->content == TRUNC)
			oflag = O_TRUNC;
		cmd->fd_out = open(file, O_CREAT | oflag | O_WRONLY, 0644);
		if (cmd->fd_out == -1)
			return (-1);
		cmd->files_out = cmd->files_out->next;
		cmd->out_modes = cmd->out_modes->next;
	}
	dup2(cmd->fd_out, 1);
	return (0);
}

static void	check_file_dir(char *name)
{
	struct stat	buf;

	stat(name, &buf);
	if (!S_ISREG(buf.st_mode) && !S_ISDIR(buf.st_mode))
		shell_error_param("No such file or directory", name);
}

int			input_redir(t_command *cmd)
{
	char	*file;

	while (cmd->files_in)
	{
		file = (char*)cmd->files_in->content;
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		check_file_dir(file);
		cmd->fd_in = open(file, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
			return (-1);
		cmd->files_in = cmd->files_in->next;
	}
	return (0);
}
