/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putchar_error.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:49:02 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/14 16:49:34 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libftprintf.h"

void	putchar_fd_error(t_flag *flags, char c, int fd)
{
	ssize_t	ret;

	ret = write(fd, &c, 1);
	if (ret < 0)
		flags->error = 1;
	++flags->count;
}
