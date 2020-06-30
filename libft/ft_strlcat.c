/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:05:14 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/10/30 11:58:08 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		j;
	int			new_length;

	i = 0;
	new_length = 0;
	while (*(dst + i) != '\0' && i < dstsize)
		i++;
	while (*(src + new_length) != '\0')
		new_length++;
	new_length += i;
	if (i + 1 < dstsize)
	{
		j = i;
		while (i + 1 < dstsize)
		{
			*(dst + i) = *(src + i - j);
			i++;
		}
		*(dst + i) = '\0';
	}
	return (new_length);
}
