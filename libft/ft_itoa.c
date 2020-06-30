/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 13:58:00 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/11 09:36:31 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		string_size(long n)
{
	int		i;

	i = 1;
	if (n < 0)
	{
		i++;
		n *= -1;
	}
	while (n >= 10)
	{
		i++;
		n /= 10;
	}
	return (i);
}

static void		number_to_string(long n, char *location)
{
	if (n >= 10)
	{
		*(location) = (n % 10) + '0';
		number_to_string(n / 10, location + 1);
	}
	else
	{
		*(location) = n + '0';
		*(location + 1) = '\0';
	}
}

static void		reverse_string(char *str)
{
	int		i;
	int		size;
	char	temp;

	size = ft_strlen(str) - 1;
	i = 0;
	while (i < size - i)
	{
		temp = *(str + i);
		*(str + i) = *(str + (size - i));
		*(str + (size - i)) = temp;
		i++;
	}
}

char			*ft_itoa(int n)
{
	long	long_n;
	char	*result;
	int		negative;
	size_t	i;

	long_n = n;
	negative = (long_n < 0) ? 1 : 0;
	result = malloc(string_size(long_n) + 1);
	if (result == NULL)
		return (NULL);
	long_n = (long_n >= 0) ? long_n : long_n * -1;
	number_to_string(long_n, result);
	if (negative)
	{
		i = ft_strlen(result);
		*(result + i) = '-';
		*(result + i + 1) = '\0';
	}
	reverse_string(result);
	return (result);
}
