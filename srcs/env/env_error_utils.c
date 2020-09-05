#include <stdlib.h>
#include <libft.h>
#include <minishell.h>

/*
**	This function will print an error if an invalid environment variable
**	is given to export or unset.
*/

void		shell_error_env(char *s, char *param)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putstr_fd(": `", STDERR_FILENO);
	ft_putstr_fd(s, STDERR_FILENO);
	ft_putendl_fd("\': not a valid identifier", STDERR_FILENO);
}
