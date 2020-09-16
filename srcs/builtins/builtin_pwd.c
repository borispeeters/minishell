/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:20:53 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:20:54 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	Builtin pwd will display the working directory that the user is in.
*/

void	builtin_pwd(t_shell *shell)
{
	char	*buf;

	(void)shell;
	buf = NULL;
	buf = getcwd(buf, 1);
	if (buf == NULL)
		shell_error_malloc();
	ft_putendl_fd(buf, STDOUT_FILENO);
	free(buf);
}
