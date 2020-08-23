#include <string.h>
#include <sys/errno.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_cd(t_shell *shell, char **vars)
{
	char	*err_msg;

	if (vars[1] && chdir(vars[1]) != 0)
	{
		write(2, "minishell: cd: ", 15);
		write(2, vars[1], ft_strlen(vars[1]));
		write(2, ": ", 2);
		err_msg = strerror(errno);
		write(2, err_msg, ft_strlen(err_msg));
		write(2, "\n", 1);
		shell->exit_status = 1;
	}
	else if (vars[1] == NULL)
	{
		if (chdir("$HOME") != 0)
		{
			write(2, "minishell: cd: HOME not set\n", 28);
			shell->exit_status = 1;
		}
	}
	
}
