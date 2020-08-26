#include "libft.h"
#include "minishell.h"

void	builtin_echo(t_shell *shell, char **vars)
{
	int	i;

	(void)shell;
	i = 1;
	if (vars[i] && ft_strcmp(vars[i], "-n") == 0)
		++i;
	while (vars[i])
	{
		write(1, vars[i], ft_strlen(vars[i]));
		++i;
		if (vars[i])
			write(1, " ", 1);
	}
	if (vars[1] && ft_strcmp(vars[1], "-n") == 0)
		return ;
	write(1, "\n", 1);
}
