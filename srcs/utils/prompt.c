#include <unistd.h>
#include <libft.h>

/*
**	General function to print the prompt for the minishell.
*/

void	write_prompt(void)
{
	ft_putstr_fd("minishell-0.1$ ", STDOUT_FILENO);
}
