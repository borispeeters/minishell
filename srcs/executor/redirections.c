#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"

static void	check_dir(char *name)
{
	struct stat	buf;

	stat(name, &buf);
	if (S_ISDIR(buf.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, name, ft_strlen(name));
		write(2, ": Is a directory\n", 17);
	}
}

int			output_redir(t_command *cmd)
{
	cmd->fd_out = 1;
	while (cmd->files_out)
	{
		if (cmd->fd_out != 1)
			close(cmd->fd_out);
		check_dir((char*)cmd->files_out->content);
		if ((t_filemode)cmd->out_modes->content == APPEND)
		{
			cmd->fd_out = open((char*)cmd->files_out->content, O_CREAT | O_APPEND | O_WRONLY, 0644);
			if (cmd->fd_out == -1)
				return (-1);
		}
		else if ((t_filemode)cmd->out_modes->content == TRUNC)
		{
			cmd->fd_out = open((char*)cmd->files_out->content, O_CREAT | O_TRUNC | O_WRONLY, 0644);
			if (cmd->fd_out == -1)
				return (-1);
		}
		cmd->files_out = cmd->files_out->next;
		cmd->out_modes = cmd->out_modes->next;
	}
	return (0);
}

static void	check_file_dir(char *name)
{
	struct stat	buf;

	stat(name, &buf);
	if (!S_ISREG(buf.st_mode) && !S_ISDIR(buf.st_mode))
	{
		write(2, "minishell: ", 11);
		write(2, name, ft_strlen(name));
		write(2, ": No such file or directory\n", 28);
	}
}

int			input_redir(t_command *cmd)
{
	cmd->fd_in = 0;
	while (cmd->files_in)
	{
		if (cmd->fd_in != 0)
			close(cmd->fd_in);
		check_file_dir((char*)cmd->files_in->content);
		cmd->fd_in = open((char*)cmd->files_in->content, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
			return (-1);
		cmd->files_in = cmd->files_in->next;
	}
	return (0);
}
