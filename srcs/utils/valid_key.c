/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   valid_key.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:36 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:37 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	Checks whether the key of a key-value pair is valid.
**	Returns non-zero for a valid key and zero for a non-valid key.
*/

int		valid_key(char *key)
{
	int	i;

	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	i = 1;
	while (key[i])
	{
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
		++i;
	}
	return (1);
}
