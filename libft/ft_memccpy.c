/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:03:57 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/05 11:47:59 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t				i;
	unsigned char		*pdst;
	const unsigned char	*psrc;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	pdst = dst;
	psrc = src;
	while (i < n)
	{
		*(pdst + i) = *(psrc + i);
		if (*(psrc + i) == (unsigned char)c)
			return (pdst + i + 1);
		i++;
	}
	return (NULL);
}
