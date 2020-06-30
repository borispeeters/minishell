/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/12/16 10:41:58 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/01/30 16:34:21 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

/*
**	The main function. It gets the buffer relevant to the fd, does an initial
**	malloc for line and then calls the read_line function.
*/

int			get_next_line(int fd, char **line)
{
	static t_fdlist		*fdlist_head = NULL;
	t_fdlist			*buf_list;
	int					read_return;

	if (fd < 0 || line == NULL || read(fd, NULL, 0) == -1)
		return (-1);
	buf_list = get_fdlist(fd, &fdlist_head);
	if (buf_list == NULL)
		return (-1);
	*line = malloc(1);
	if (*line == NULL)
		return (-1);
	**line = '\0';
	read_return = read_line(fd, line, buf_list->buf);
	if (read_return == 0)
		fdlist_remove(&fdlist_head, fd);
	if (read_return < 0)
		fdlist_clear(&fdlist_head);
	return (read_return);
}

/*
**	This function checks the buffer and/or reads the file and puts the result
**	in the line variable.
*/

int			read_line(int fd, char **line, char *buffer)
{
	int		read_return;

	read_return = 1;
	if (*buffer == 0)
		read_return = read(fd, buffer, BUFFER_SIZE);
	while (gnl_strchr(buffer, '\n') == -1 && read_return > 0)
	{
		gnl_strjoin(line, buffer);
		if (line == NULL)
			return (-1);
		shift_buffer(buffer, 0);
		read_return = read(fd, buffer, BUFFER_SIZE);
	}
	gnl_strjoin(line, buffer);
	if (line == NULL)
		return (-1);
	shift_buffer(buffer, gnl_strchr(buffer, '\n') + 1);
	if (read_return > 0)
		return (1);
	else if (read_return == 0)
		return (0);
	return (-1);
}

/*
**	This function will join strings s1 and s2, and put the pointer of s1 to the
**	new string. It will free the original s1.
*/

void		gnl_strjoin(char **s1, char *s2)
{
	char	*result;
	int		first_len;
	int		second_len;

	if (*s1 == NULL)
		return ;
	first_len = gnl_strlen(*s1);
	second_len = gnl_strlen(s2);
	result = malloc(first_len + second_len + 1);
	if (result == NULL)
	{
		free(*s1);
		*s1 = NULL;
		return ;
	}
	gnl_strcpy(result, *s1);
	gnl_strcpy(result + first_len, s2);
	*(result + first_len + second_len) = '\0';
	free(*s1);
	*s1 = result;
}

/*
**	This function will count the length to the first occurence of either the
** '\0' or '\n' characters.
*/

int			gnl_strlen(char *str)
{
	int		length;

	length = 0;
	while (*(str + length) != '\0' && *(str + length) != '\n')
		length++;
	return (length);
}

/*
**	This function will copy a string terminated by either '\0' or '\n' to the
**	pointer given.
*/

void		gnl_strcpy(char *dst, char *src)
{
	int		i;

	i = 0;
	while (*(src + i) != '\0' && *(src + i) != '\n')
	{
		*(dst + i) = *(src + i);
		i++;
	}
}
