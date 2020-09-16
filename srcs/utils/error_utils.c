/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:21 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:22 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"

/*
**	This function will print an error to the error stream.
*/

void		shell_error(char *message)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
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

void		shell_error_malloc(void)
{
	shell_error("malloc failed");
	exit(EXIT_FAILURE);
}

/*
**	This function will print a syntax error to the error stream.
*/

void		shell_error_syntax(char *token)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("syntax error near unexpected token `", STDERR_FILENO);
	ft_putchar_fd(*token, STDERR_FILENO);
	ft_putendl_fd("\'", STDERR_FILENO);
}

/*
**	This function will print 2 parameters and then the error message.
*/

void		shell_error_builtin_param(char *message, char *builtin, char *param)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(builtin, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putstr_fd(param, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(message, STDERR_FILENO);
}
