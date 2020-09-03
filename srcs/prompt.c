#include <unistd.h>
#include "libft.h"

void	write_prompt(void)
{
	ft_putstr_fd("minishell-0.1$ ", STDOUT_FILENO);
}
