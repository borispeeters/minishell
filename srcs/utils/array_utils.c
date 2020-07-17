/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   array_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/15 10:52:31 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/15 11:16:01 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/*
**	This function will malloc a 2-dimensional char array with n elements,
**	all set to NULL.
*/

char		**malloc_var_array(int n)
{
	char	**array;
	int		i;

	if (n <= 1)
		return (NULL);
	array = malloc(sizeof(char *) * (n + 1));
	if (array == NULL)
		return (NULL);
	i = 0;
	while (i < n)
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
	int		i;

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
