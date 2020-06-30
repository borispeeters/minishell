/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 09:06:39 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/11 09:27:03 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	int		result_size;
	int		i;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	result_size = ft_strlen(s1) + ft_strlen(s2);
	result = malloc(result_size + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		*(result + i) = *(s1 + i);
		i++;
	}
	result_size = 0;
	while (*(s2 + result_size) != '\0')
	{
		*(result + i + result_size) = *(s2 + result_size);
		result_size++;
	}
	*(result + i + result_size) = '\0';
	return (result);
}
