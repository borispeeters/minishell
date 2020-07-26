#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include "minishell.h"

int		output_redir(t_command *cmd)
{
	struct stat	buf;

	cmd->fd_out = 1;
	while (cmd->files_out)
	{
		if (cmd->fd_out != 1)
		{
			if (close(cmd->fd_out) != 0)
				return (-1);
		}
		stat((char*)cmd->files_out->content, &buf);
		if (S_ISDIR(buf.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, (char*)cmd->files_out->content, ft_strlen((char*)cmd->files_out->content));
			write(2, ": Is a directory\n", 17);
		}
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
	if (dup2(cmd->fd_out, 1) == -1)
		return (-1);
	return (0);
}

int		input_redir(t_command *cmd)
{
	struct stat	buf;

	cmd->fd_in = 0;
	while (cmd->files_in)
	{
		if (cmd->fd_in != 0)
		{
			if (close(cmd->fd_in) != 0)
				return (-1);
		}
		stat((char*)cmd->files_in->content, &buf);
		if (!S_ISREG(buf.st_mode) && !S_ISDIR(buf.st_mode))
		{
			write(2, "minishell: ", 11);
			write(2, (char*)cmd->files_in->content, ft_strlen((char*)cmd->files_in->content));
			write(2, ": No such file or directory\n", 28);
		}
		cmd->fd_in = open((char*)cmd->files_in->content, O_RDONLY, 0644);
		if (cmd->fd_in == -1)
			return (-1);
		cmd->files_in = cmd->files_in->next;
	}
	if (dup2(cmd->fd_in, 0) == -1)
		return (-1);
	return (0);
}
