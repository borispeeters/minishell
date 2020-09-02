#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_echo(t_shell *shell, t_env *env, t_command *cmd)
{
	int	i;
	int	print_newline;

	(void)shell;
	(void)env;
	print_newline = 1;
	i = 1;
	if (cmd->vars[i] && ft_strcmp(cmd->vars[i], "-n") == 0)
	{
		print_newline = 0;
		++i;
	}
	while (cmd->vars[i])
	{
		ft_putstr_fd(cmd->vars[i], STDOUT_FILENO);
		++i;
		if (cmd->vars[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
