/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_checks.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:51:30 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/14 17:26:58 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include "libft/libft.h"

void	check_flag(const char **format, t_flag *flags)
{
	while (**format && !ft_isalpha_perc(**format) && **format != '.' \
	&& !ft_isposdigit(**format) && **format != '*')
	{
		if (**format == '0' && flags->flag_type != '-')
			flags->flag_type = '0';
		else if (**format == '-')
			flags->flag_type = '-';
		++(*format);
	}
}

void	check_width(const char **format, t_flag *flags, va_list args)
{
	while (**format && !ft_isalpha_perc(**format) && **format != '.')
	{
		if (ft_isposdigit(**format))
		{
			flags->width = ft_atoi(*format);
			return ;
		}
		else if (**format == '*')
		{
			flags->width = va_arg(args, int);
			if (flags->width < 0)
			{
				flags->width *= -1;
				flags->flag_type = '-';
			}
			return ;
		}
		++(*format);
	}
}

void	check_precision(const char **format, t_flag *flags, va_list args)
{
	while (**format && !ft_isalpha_perc(**format))
	{
		if (**format == '.')
			flags->precision = 0;
		else if (ft_isdigit(**format) && flags->precision == 0)
			flags->precision = ft_atoi(*format);
		else if (**format == '*' && flags->precision == 0)
			flags->precision = va_arg(args, int);
		++(*format);
	}
}

void	check_data(const char **format, t_flag *flags)
{
	while (**format)
	{
		if (**format == '%' || **format == 'p')
			flags->data_type = (**format == '%') ? '%' : 'p';
		else if (**format == 'u' || **format == 'd' || **format == 'i')
			flags->data_type = (**format == 'u') ? 'u' : 'd';
		else if (**format == 'x' || **format == 'X')
			flags->data_type = (**format == 'x') ? 'x' : 'X';
		else if (**format == 'c' || **format == 's')
			flags->data_type = (**format == 'c') ? 'c' : 's';
		else if (ft_isalpha_perc(**format))
			flags->data_type = '!';
		++(*format);
		if (flags->data_type != ' ')
			return ;
	}
}

void	check_print(t_flag *flags, va_list args)
{
	if (flags->data_type == '%')
		print_char(flags, '%');
	else if (flags->data_type == 'p')
		print_addr(flags, va_arg(args, unsigned long));
	else if (flags->data_type == 'u')
		print_uint(flags, va_arg(args, unsigned int));
	else if (flags->data_type == 'd')
		print_int(flags, va_arg(args, int));
	else if (flags->data_type == 'x')
		print_hex(flags, va_arg(args, unsigned int), 's');
	else if (flags->data_type == 'X')
		print_hex(flags, va_arg(args, unsigned int), 'B');
	else if (flags->data_type == 'c')
		print_char(flags, va_arg(args, int));
	else if (flags->data_type == 's')
		print_str(flags, va_arg(args, char*));
}
