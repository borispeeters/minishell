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
		check_dir(file);
		if (*((t_filemode*)tmp_out_modes->content) == APPEND)
			oflag = O_APPEND;
		else if (*((t_filemode*)tmp_out_modes->content) == TRUNC)
			oflag = O_TRUNC;
		cmd->fd_out = open(file, O_CREAT | oflag | O_WRONLY, 0644);
		if (cmd->fd_out == -1)
			return (-1);
		tmp_files_out = tmp_files_out->next;
		tmp_out_modes = tmp_out_modes->next;
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

	cmd->fd_in = 0;
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
	dup2(cmd->fd_in, 0);
	return (0);
}
