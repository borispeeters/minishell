/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 09:43:42 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/05 11:46:23 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char		*pdst;
	const unsigned char	*psrc;
	size_t				i;

	if (dst == NULL && src == NULL)
		return (NULL);
	i = 0;
	pdst = dst;
	psrc = src;
	while (i < n)
	{
		*(pdst + i) = *(psrc + i);
		i++;
	}
	return (dst);
}
