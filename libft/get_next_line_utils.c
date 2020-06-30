/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/17 11:07:46 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/01/30 16:34:29 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

/*
**	This function will return the first occurence of the character 'c' in the
**	character string 'str'. Returns -1 if not found.
*/

int			gnl_strchr(char *str, char c)
{
	int		position;

	position = 0;
	while (*(str + position) != '\0')
	{
		if (*(str + position) == c)
			return (position);
		position++;
	}
	if (c == '\0')
		return (position);
	return (-1);
}

/*
**	This function will copy the contents from the 'n' position to the start,
**	and fill the rest with 0. An 'n' higher than or equal to BUFFER_SIZE, or
**	lower than or equal to 0 will just clear the buffer entirely.
*/

void		shift_buffer(char *buffer, int n)
{
	int		i;

	if (n <= 0)
		n = BUFFER_SIZE;
	i = 0;
	while (n + i < BUFFER_SIZE)
	{
		*(buffer + i) = *(buffer + n + i);
		i++;
	}
	while (i < BUFFER_SIZE)
	{
		*(buffer + i) = 0;
		i++;
	}
}

/*
**	This function will return the correct buffer out of the list.
*/

t_fdlist	*get_fdlist(int fd, t_fdlist **head)
{
	t_fdlist	*elem;
	char		*buffer;

	elem = *head;
	while (elem != NULL)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	elem = (t_fdlist*)malloc(sizeof(t_fdlist));
	if (elem == NULL)
		return (fdlist_clear(head));
	elem->fd = fd;
	elem->next = *head;
	*head = elem;
	buffer = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (buffer == NULL)
		return (fdlist_clear(head));
	*(buffer + BUFFER_SIZE) = '\0';
	shift_buffer(buffer, 0);
	elem->buf = buffer;
	return (elem);
}

/*
**	This function will clear the entire list in case of an error.
*/

void		*fdlist_clear(t_fdlist **head)
{
	t_fdlist	*elem;
	t_fdlist	*next;

	elem = *head;
	while (elem)
	{
		next = elem->next;
		free(elem->buf);
		free(elem);
		elem = next;
	}
	*head = NULL;
	return (NULL);
}

/*
**	This function will remove a link from the list.
*/

void		fdlist_remove(t_fdlist **head, int fd)
{
	t_fdlist	*elem;
	t_fdlist	*prev;

	elem = *head;
	prev = NULL;
	while (elem)
	{
		if (elem->fd == fd)
		{
			if (elem == *head)
				*head = elem->next;
			else
				prev->next = elem->next;
			free(elem->buf);
			free(elem);
			break ;
		}
		prev = elem;
		elem = elem->next;
	}
}
