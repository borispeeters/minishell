#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_pwd(t_shell *shell)
{
	char	*buf;

	(void)shell;
	buf = NULL;
	buf = getcwd(buf, 1);
	if (buf == NULL)
		shell_error_malloc();
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
}
