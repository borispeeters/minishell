/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shell_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 10:00:57 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/16 14:48:28 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free_content(void *content)
{
	free(content);
}

int		is_space(int c)
{
	return (c == ' ' || c == '\t');
}

int		is_metacharacter(int c)
{
	char	metachar[8];
	int		i;

	ft_strlcpy(metachar, "\n|;()<>", 8);
	i = 0;
	while (metachar[i])
	{
		if (c == metachar[i])
			return (1);
		++i;
	}
	return (0);
}
