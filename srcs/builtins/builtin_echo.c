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
		write(1, vars[i], ft_strlen(vars[i]));
		++i;
		if (vars[i])
			write(1, " ", 1);
	}
	if (print_newline)
		write(1, "\n", 1);
}
