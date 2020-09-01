#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	builtin_echo(t_shell *shell, char **vars)
{
	int	i;
	int	print_newline;

	print_newline = 1;
	(void)shell;
	i = 1;
	if (vars[i] && ft_strcmp(vars[i], "-n") == 0)
	{
		print_newline = 0;
		++i;
	}
	while (vars[i])
	{
		ft_putstr_fd(vars[i], STDOUT_FILENO);
		++i;
		if (vars[i])
			ft_putchar_fd(' ', STDOUT_FILENO);
	}
	if (print_newline)
		ft_putchar_fd('\n', STDOUT_FILENO);
}
