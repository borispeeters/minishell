/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strmapi.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 09:29:07 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/04 13:18:51 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*result;
	int		i;

	if (s == NULL)
		return (NULL);
	i = 0;
	result = malloc(ft_strlen(s) + 1);
	if (result == NULL)
		return (NULL);
	while (*(s + i) != '\0')
	{
		*(result + i) = f(i, *(s + i));
		i++;
	}
	*(result + i) = '\0';
	return (result);
}
