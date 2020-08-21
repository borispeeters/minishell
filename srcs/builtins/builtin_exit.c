#include "minishell.h"

void	builtin_exit(t_shell *shell)
{
	shell->status = 0;
}
