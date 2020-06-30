/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strdup.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 15:25:16 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/07 09:08:58 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strdup(const char *s1)
{
	int		i;
	char	*result;

	i = 0;
	while (*(s1 + i) != '\0')
		i++;
	result = malloc(i + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*(s1 + i) != '\0')
	{
		*(result + i) = *(s1 + i);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}
