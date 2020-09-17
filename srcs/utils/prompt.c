/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   prompt.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:29 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/17 10:31:28 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

/*
**	General function to print the prompt for the minishell.
*/

void	write_prompt(void)
{
	ft_putstr_fd("minishell-1.0$ ", STDOUT_FILENO);
}
