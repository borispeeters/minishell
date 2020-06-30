/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:28:06 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/05 11:48:33 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t				i;
	unsigned char		*pdst;
	const unsigned char	*psrc;

	if (dst == NULL && src == NULL)
		return (dst);
	pdst = dst;
	psrc = src;
	i = 0;
	while (i < len)
	{
		if (dst > src)
			*(pdst + (len - i - 1)) = *(psrc + (len - i - 1));
		else
			*(pdst + i) = *(psrc + i);
		i++;
	}
	return (dst);
}
