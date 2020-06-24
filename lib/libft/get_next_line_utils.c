/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 14:30:55 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/10 20:12:06 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

void	prep_buf(char *buf)
{
	char	*begin;
	char	*end;

	begin = buf;
	end = buf;
	while (*end)
	{
		if (*end == '\n')
		{
			++end;
			break ;
		}
		++end;
	}
	while (*end)
	{
		*begin = *end;
		++begin;
		++end;
	}
	*begin = '\0';
}

size_t	line_len(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		++i;
	return (i);
}

int		eol_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		++i;
	}
	return (0);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	str = malloc(sizeof(char) * (line_len(s1) + line_len(s2) + 1));
	if (!str)
	{
		free((void*)s1);
		return (NULL);
	}
	while (s1[i])
	{
		str[i] = s1[i];
		++i;
	}
	j = 0;
	while (s2[j] && s2[j] != '\n')
	{
		str[i + j] = s2[j];
		++j;
	}
	free((void*)s1);
	str[i + j] = '\0';
	return (str);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		i;

	i = 0;
	s2 = (char*)malloc(sizeof(char) * (line_len(s1) + 1));
	if (!s2)
		return (0);
	while (s1[i])
	{
		s2[i] = (char)s1[i];
		++i;
	}
	s2[i] = '\0';
	return (s2);
}
