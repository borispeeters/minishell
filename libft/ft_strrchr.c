/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strrchr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 12:13:41 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/10/30 12:20:47 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		last_found;
	int		found;

	i = 0;
	last_found = 0;
	found = 0;
	while (*(s + i) != '\0')
	{
		if (*(s + i) == c)
		{
			last_found = i;
			found = 1;
		}
		i++;
	}
	if (c == '\0')
		return ((char*)s + i);
	if (found)
		return ((char*)s + last_found);
	return (NULL);
}
