/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:22:54 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/06 13:06:13 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	match;

	if (*needle == '\0' || len == 0)
		return ((char*)haystack);
	i = 0;
	match = 0;
	while (i < len && haystack[i] != '\0')
	{
		if (haystack[i] == needle[0])
		{
			match = 0;
			while (haystack[i + match] == needle[match])
			{
				if (i + match > len)
					return (NULL);
				match++;
				if (needle[match] == '\0')
					return ((char*)haystack + i);
			}
		}
		i++;
	}
	return (NULL);
}
