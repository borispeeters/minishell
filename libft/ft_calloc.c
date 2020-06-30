/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 14:55:05 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/10/30 15:25:07 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total_bytes;
	size_t			i;
	void			*memory;
	unsigned char	*byte_pointer;

	total_bytes = count * size;
	memory = malloc(total_bytes);
	if (memory == NULL)
		return (NULL);
	byte_pointer = (unsigned char*)memory;
	i = 0;
	while (i < total_bytes)
	{
		*(byte_pointer + i) = 0;
		i++;
	}
	return (memory);
}
