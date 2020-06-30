/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 09:22:09 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/11 13:27:44 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static void		copy_part(char const *src, char *dst, int start, int len)
{
	int		i;

	i = 0;
	while (i < len)
	{
		*(dst + i) = *(src + i + start);
		i++;
	}
	*(dst + i) = '\0';
}

char			*ft_strtrim(char const *s1, char const *set)
{
	char	*result;
	int		result_size;
	int		i;

	if (s1 == NULL || set == NULL)
		return (NULL);
	result_size = ft_strlen(s1);
	i = 1;
	while (i <= result_size && ft_strchr(set, *(s1 + (result_size - i))))
		i++;
	if (i >= result_size)
		return (ft_strdup(""));
	result_size -= (i - 1);
	i = 0;
	while (ft_strchr(set, *(s1 + i)))
		i++;
	result_size -= i;
	result = malloc(result_size + 1);
	if (result == NULL)
		return (NULL);
	copy_part(s1, result, i, result_size);
	return (result);
}
