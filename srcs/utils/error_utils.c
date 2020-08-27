#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

/*
**	This function will print an error to the error stream.
*/

void		shell_error(char const *message)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
}

/*
**	This function will print an error related to a parameter
**	to the error stream.
*/

void		shell_error_param(char const *message, char const *param)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, param, ft_strlen(param));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, message, ft_strlen(message));
	write(STDERR_FILENO, "\n", 1);
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

void		shell_error_syntax(char const *str)
{
	write(STDERR_FILENO, "minishell: ", 11);
	write(STDERR_FILENO, "syntax error near unexpected token `", 36);
	write(STDERR_FILENO, str, 1);
	write(STDERR_FILENO, "'\n", 2);
}
