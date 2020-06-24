/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/09 19:10:25 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/11 16:08:06 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdlib.h>

void	flag_init(t_flag *flags)
{
	flags->data_type = ' ';
	flags->flag_type = ' ';
	flags->width = 0;
	flags->precision = -1;
}

void	checks(const char **format, t_flag *flags, va_list args)
{
	while (**format && !flags->error)
	{
		flag_init(flags);
		if (**format == '%')
		{
			++(*format);
			check_flag(format, flags);
			check_width(format, flags, args);
			check_precision(format, flags, args);
			check_data(format, flags);
			if (flags->data_type != '!')
				check_print(flags, args);
		}
		else
		{
			if (!flags->error)
				putchar_fd_error(flags, **format, 1);
			++(*format);
		}
	}
}

int		ft_printf(const char *format, ...)
{
	va_list		args;
	t_flag		flags;

	flags.count = 0;
	flags.error = 0;
	va_start(args, format);
	checks(&format, &flags, args);
	va_end(args);
	if (flags.error)
		return (-1);
	return (flags.count);
}
