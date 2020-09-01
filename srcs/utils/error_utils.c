#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

/*
**	This function will print an error to the error stream.
*/

void		shell_error(char *message)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

/*
**	This function will print an error related to a parameter
**	to the error stream.
*/

void		shell_error_param(char *message, char *param)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}

/*
**	This function will inform the user that malloc failed 
**	and then exit the shell.
*/

void		shell_error_malloc()
{
	shell_error("malloc failed");
	exit(EXIT_FAILURE);
}

/*
**	This function will print a syntax error to the error stream.
*/

void		shell_error_syntax(char *s)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	write(STDERR_FILENO, s, 1);
	ft_putendl_fd("\'", STDERR_FILENO);
}

