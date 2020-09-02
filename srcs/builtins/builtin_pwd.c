#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_pwd(t_shell *shell, t_env *env, t_command *cmd)
{
	char	*buf;

	(void)shell;
	(void)env;
	(void)cmd;
	buf = NULL;
	buf = getcwd(buf, 1);
	if (buf == NULL)
		shell_error_malloc();
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
}
