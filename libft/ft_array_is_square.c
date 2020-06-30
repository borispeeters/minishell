/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_array_is_square.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/02/05 14:08:43 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/02/05 14:11:18 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_array_is_square(char **array)
{
	int		line_length;

	line_length = (int)ft_strlen(*array);
	while (*array != NULL)
	{
		if ((int)ft_strlen(*array) != line_length)
			return (0);
		array++;
	}
	return (1);
}
