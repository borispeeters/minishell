/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lengths.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/14 16:34:10 by bpeeters       #+#    #+#                */
/*   Updated: 2020/01/14 16:35:54 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"

size_t	ft_hexlen(unsigned long x)
{
	size_t i;

	i = 1;
	while (x >= 16)
	{
		x /= 16;
		++i;
	}
	return (i);
}

size_t	ft_intlen(int n)
{
	size_t i;

	i = 1;
	if (n == -2147483648)
		return (10);
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		n /= 10;
		++i;
	}
	return (i);
}

size_t	ft_uintlen(unsigned int u)
{
	size_t i;

	i = 1;
	while (u > 9)
	{
		u /= 10;
		++i;
	}
	return (i);
}
