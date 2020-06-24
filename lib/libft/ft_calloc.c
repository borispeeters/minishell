/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 19:12:40 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/03/10 19:40:27 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t	len;
	size_t	i;
	void	*ret;
	char	*str;

	len = count * size;
	ret = malloc(len);
	if (!ret)
		return (0);
	str = ret;
	i = 0;
	while (i < len)
	{
		str[i] = 0;
		i++;
	}
	return (ret);
}
