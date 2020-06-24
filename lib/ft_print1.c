/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print1.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:02:20 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/14 17:21:16 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_padding(t_flag *flags, int len, char c)
{
	while (len > 0 && !flags->error)
	{
		putchar_fd_error(flags, c, 1);
		--len;
	}
}

void	print_uint(t_flag *flags, unsigned int u)
{
	int	len;
	int	prec;

	len = ft_uintlen(u);
	prec = flags->precision;
	if (u == 0 && flags->precision == 0)
		++flags->width;
	if (flags->precision >= 0 && flags->flag_type == '0')
		flags->flag_type = ' ';
	flags->precision = flags->precision - len;
	if (flags->precision >= 0)
		flags->width = flags->width - flags->precision - len;
	else
		flags->width = flags->width - len;
	if (flags->flag_type != '-')
		print_padding(flags, flags->width, flags->flag_type);
	print_padding(flags, flags->precision, '0');
	if (u != 0 || prec != 0)
		putunbr_fd_error(flags, u, 1);
	if (flags->flag_type == '-')
		print_padding(flags, flags->width, ' ');
}

void	print_int(t_flag *flags, int n)
{
	int	prec;

	prec = flags->precision;
	if (n == 0 && flags->precision == 0)
		++flags->width;
	if (flags->precision >= 0 && flags->flag_type == '0')
		flags->flag_type = ' ';
	flags->precision = flags->precision - ft_intlen(n);
	flags->width = flags->width - ft_intlen(n);
	if (flags->precision >= 0)
		flags->width = flags->width - flags->precision;
	if (n < 0)
		flags->width = flags->width - 1;
	if (flags->flag_type == ' ')
		print_padding(flags, flags->width, ' ');
	if (n < 0 && !flags->error)
		putchar_fd_error(flags, '-', 1);
	if (flags->flag_type == '0')
		print_padding(flags, flags->width, '0');
	print_padding(flags, flags->precision, '0');
	if (n != 0 || prec != 0)
		putnbr_fd_error(flags, n, 1);
	if (flags->flag_type == '-')
		print_padding(flags, flags->width, ' ');
}
