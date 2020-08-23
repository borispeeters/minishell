#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_exit(t_shell *shell, char **vars)
{
	if (vars[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments", 35);
		shell->exit_status = 1;
		return ;
	}
	shell->exit_status = 0;
	if (vars[1])
		shell->exit_status = ft_atoi(vars[1]);
	shell->status = 0;
}
