#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_pwd(t_shell *shell)
{
	char	*buf;

	buf = NULL;
	buf = getcwd(buf, 1);
	if (buf == NULL)
	{
		write(2, "minishell: pwd: malloc failed\n", 30);
		return ;
	}
	write(1, buf, ft_strlen(buf));
	write(1, "\n", 1);
	free(buf);
	shell->exit_status = 0;
}
