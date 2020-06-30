/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_removechar.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 09:24:39 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/02/05 11:22:40 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	new_string_length(char *string, char c)
{
	int		i;

	i = 0;
	while (*string != '\0')
	{
		if (*string != c)
			i++;
		string++;
	}
	return (i);
}

char		*ft_removechar(char *string, char c)
{
	int		i;
	int		new_length;
	char	*result;

	new_length = new_string_length(string, c);
	result = malloc(new_length + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*string != '\0')
	{
		if (*string != c)
		{
			*(result + i) = *string;
			i++;
		}
		string++;
	}
	*(result + i) = '\0';
	return (result);
}
