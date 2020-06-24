/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   libftprintf.h                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/10 17:08:46 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/11 18:13:50 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFTPRINTF_H
# define LIBFTPRINTF_H

# include "libft/libft.h"
# include "libft/get_next_line.h"
# include <stdarg.h>

typedef	struct	s_flag
{
	char		data_type;
	char		flag_type;
	int			width;
	int			precision;
	int			count;
	int			error;
}				t_flag;

int				ft_printf(const char *format, ...);
void			checks(const char **format, t_flag *flags, va_list args);
size_t			ft_hexlen(unsigned long x);
size_t			ft_intlen(int n);
size_t			ft_uintlen(unsigned int u);
int				ft_isposdigit(int c);
int				ft_isalpha_perc(int c);
void			check_flag(const char **format, t_flag *flags);
void			check_width(const char **format, t_flag *flags, va_list args);
void			check_precision(const char **format, \
				t_flag *flags, va_list args);
void			check_data(const char **format, t_flag *flags);
void			check_print(t_flag *flags, va_list args);
void			print_padding(t_flag *flags, int len, char c);
void			print_uint(t_flag *flags, unsigned int u);
void			print_int(t_flag *flags, int n);
void			print_addr(t_flag *flags, unsigned long p);
void			print_hex(t_flag *flags, unsigned int x, char c);
void			print_char(t_flag *flags, char c);
void			print_str(t_flag *flags, char *s);
void			putchar_fd_error(t_flag *flags, char c, int fd);
void			putstr_fd_len_error(t_flag *flags, char *s, int len, int fd);
void			putnbr_fd_error(t_flag *flags, int n, int fd);
void			putunbr_fd_error(t_flag *flags, unsigned int u, int fd);
void			puthex_fd_error(t_flag *flags, unsigned int x, int fd, char c);
void			putaddr_fd_error(t_flag *flags, unsigned long p, \
				int prec, int fd);

#endif
