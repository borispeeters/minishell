/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:16 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:17 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "minishell.h"

/*
**	Returns the length of a string array.
*/

int			arrlen(char **array)
{
	int	i;

	i = 0;
	while (array[i])
		++i;
	return (i);
}

/*
**	This function will malloc a 2-dimensional char array with n elements,
**	all set to NULL.
*/

char		**malloc_var_array(int n)
{
	char	**array;
	int		i;

	array = malloc(sizeof(char *) * (n + 1));
	if (array == NULL)
		shell_error_malloc();
	i = 0;
	while (i <= n)
	{
		*(array + i) = NULL;
		i++;
	}
	return (array);
}

/*
**	This function will free a 2-dimensional char array and all its elements.
*/

void		free_var_array(char **array)
{
	int	i;

	i = 0;
	while (*(array + i) != NULL)
	{
		free(*(array + i));
		*(array + i) = NULL;
		i++;
	}
	free(array);
	array = NULL;
}
