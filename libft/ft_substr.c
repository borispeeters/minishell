/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:48:43 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/02/03 11:41:04 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;
	size_t	i;

	size = 0;
	if (s == NULL)
		return (NULL);
	while (*(s + size) != '\0')
		size++;
	if (size < start)
		return (ft_strdup(""));
	size -= start;
	size = (len < size) ? len : size;
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < size)
	{
		result[i] = s[start + i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
