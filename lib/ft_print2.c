/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_print2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 17:02:40 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/14 17:04:17 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

void	print_addr(t_flag *flags, unsigned long p)
{
	int	len;
	int	prec;

	len = ft_hexlen(p);
	prec = flags->precision;
	if (!p && flags->precision == 0)
		++flags->width;
	if (flags->precision >= 0 && flags->flag_type == '0')
		flags->flag_type = ' ';
	flags->precision = flags->precision - len;
	if (flags->precision >= 0)
		flags->width = flags->width - flags->precision - len - 2;
	else
		flags->width = flags->width - len - 2;
	if (flags->flag_type == ' ')
		print_padding(flags, flags->width, ' ');
	putstr_fd_len_error(flags, "0x", 2, 1);
	if (flags->flag_type == '0')
		print_padding(flags, flags->width, '0');
	print_padding(flags, flags->precision, '0');
	putaddr_fd_error(flags, p, prec, 1);
	if (flags->flag_type == '-')
		print_padding(flags, flags->width, ' ');
}

void	print_hex(t_flag *flags, unsigned int x, char c)
{
	int	len;
	int	prec;

	len = ft_hexlen(x);
	prec = flags->precision;
	if (x == 0 && flags->precision == 0)
		++flags->width;
	if (flags->precision >= 0 && flags->flag_type == '0')
		flags->flag_type = ' ';
	flags->precision = flags->precision - len;
	if (flags->precision >= 0)
		flags->width = flags->width - flags->precision - len;
	else
		flags->width = flags->width - len;
	if (flags->width > 0 && flags->flag_type != '-')
		print_padding(flags, flags->width, flags->flag_type);
	print_padding(flags, flags->precision, '0');
	if (x != 0 || prec != 0)
		puthex_fd_error(flags, x, 1, c);
	if (flags->flag_type == '-')
		print_padding(flags, flags->width, ' ');
}

void	print_char(t_flag *flags, char c)
{
	flags->width = flags->width - 1;
	if (flags->flag_type != '-')
		print_padding(flags, flags->width, flags->flag_type);
	if (!flags->error)
		putchar_fd_error(flags, c, 1);
	if (flags->flag_type == '-')
		print_padding(flags, flags->width, ' ');
}

void	print_str(t_flag *flags, char *s)
{
	int	len;

	if (s == NULL)
		s = "(null)";
	len = ft_strlen(s);
	if (len > flags->precision && flags->precision >= 0)
		len = flags->precision;
	flags->width = flags->width - len;
	if (flags->flag_type != '-')
		print_padding(flags, flags->width, flags->flag_type);
	putstr_fd_len_error(flags, s, len, 1);
	if (flags->flag_type == '-')
		print_padding(flags, flags->width, ' ');
}
