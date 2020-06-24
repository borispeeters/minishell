/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   putstuff_fd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 17:01:41 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/14 16:49:42 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <unistd.h>

void	putstr_fd_len_error(t_flag *flags, char *s, int len, int fd)
{
	int	i;

	i = 0;
	if (!s)
		return ;
	while (s[i] && len > 0 && !flags->error)
	{
		putchar_fd_error(flags, s[i], fd);
		++i;
		--len;
	}
}

void	putnbr_fd_error(t_flag *flags, int n, int fd)
{
	if (n == -2147483648)
	{
		putstr_fd_len_error(flags, "2147483648", 10, fd);
		return ;
	}
	if (n < 0)
		n *= -1;
	if (n > 9)
		putnbr_fd_error(flags, n / 10, fd);
	if (!flags->error)
		putchar_fd_error(flags, n % 10 + '0', fd);
}

void	putunbr_fd_error(t_flag *flags, unsigned int u, int fd)
{
	if (u > 9)
		putunbr_fd_error(flags, u / 10, fd);
	if (!flags->error)
		putchar_fd_error(flags, u % 10 + '0', fd);
}

void	puthex_fd_error(t_flag *flags, unsigned int x, int fd, char c)
{
	if (x >= 16)
		puthex_fd_error(flags, x / 16, fd, c);
	x %= 16;
	if (x > 9 && c == 's')
		x += 87;
	else if (x > 9 && c == 'B')
		x += 55;
	else
		x += '0';
	if (!flags->error)
		putchar_fd_error(flags, x, fd);
}

void	putaddr_fd_error(t_flag *flags, unsigned long p, int prec, int fd)
{
	if (!p && prec == 0)
		return ;
	if (p >= 16)
		putaddr_fd_error(flags, p / 16, prec, fd);
	p %= 16;
	if (p > 9)
		p += 87;
	else
		p += '0';
	if (!flags->error)
		putchar_fd_error(flags, p, 1);
}
