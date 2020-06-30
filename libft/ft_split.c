/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/31 11:18:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/02/03 15:16:09 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int		count(char const *str, char c)
{
	int		segments;
	int		current_split;

	current_split = 0;
	segments = 0;
	if (*str != '\0' && *str != c)
		segments++;
	while (*str != '\0')
	{
		if (*str == c && current_split == 0)
		{
			current_split = 1;
			segments++;
		}
		if (*str != c && current_split == 1)
		{
			current_split = 0;
		}
		str++;
	}
	if (current_split)
		segments--;
	return (segments);
}

static int		match_at_start(char const *str, char c)
{
	int		amount;

	amount = 0;
	while (*str == c)
	{
		amount++;
		str++;
	}
	return (amount);
}

static char		*copy_up_to(char const *src, char c)
{
	char	*result;
	int		size;
	int		i;

	size = 0;
	while (*(src + size) != c && *(src + size) != '\0')
		size++;
	result = malloc(size + 1);
	if (result == NULL)
		return (NULL);
	i = 0;
	while (*(src + i) != c && *(src + i) != '\0')
	{
		*(result + i) = *(src + i);
		i++;
	}
	*(result + i) = '\0';
	return (result);
}

static void		free_everything(char **result, int amount)
{
	int		i;

	i = 0;
	while (i < amount)
	{
		free(*(result + i));
		i++;
	}
	free(result);
}

char			**ft_split(char const *s, char c)
{
	char	**result;
	int		i;
	int		segments;

	if (s == NULL)
		return (NULL);
	segments = count(s, c);
	result = malloc(sizeof(char*) * (segments + 1));
	if (result == NULL)
		return (NULL);
	i = 0;
	while (i < segments)
	{
		s += match_at_start(s, c);
		*(result + i) = copy_up_to(s, c);
		if (*(result + i) == NULL)
		{
			free_everything(result, i);
			return (NULL);
		}
		s += ft_strlen(*(result + i)) + 1;
		i++;
	}
	*(result + i) = NULL;
	return (result);
}
