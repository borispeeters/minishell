/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 14:25:55 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/10 20:11:50 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

t_gnl	*lst_clear(t_gnl **head)
{
	t_gnl	*node;
	t_gnl	*temp;

	node = *head;
	while (node)
	{
		temp = node->next;
		free(node);
		node = temp;
	}
	*head = NULL;
	return (NULL);
}

t_gnl	*checklst_add(t_gnl **head, int fd)
{
	t_gnl	*node;
	t_gnl	*new;

	if (read(fd, 0, 0) < 0)
		return (NULL);
	node = *head;
	while (node)
	{
		if (node->fd == fd)
			return (node);
		node = node->next;
	}
	new = (t_gnl*)malloc(sizeof(t_gnl));
	if (!new)
		return (lst_clear(head));
	new->fd = fd;
	new->sz = 1;
	new->buf[0] = '\0';
	new->next = *head;
	new->previous = NULL;
	if (*head != NULL)
		(*head)->previous = new;
	*head = new;
	return (new);
}

int		clear_node(t_gnl **head, t_gnl *fbuf, ssize_t ret)
{
	if (fbuf->previous == NULL && fbuf->next == NULL)
		free(fbuf);
	else if (fbuf->previous == NULL)
	{
		*head = fbuf->next;
		(*head)->previous = NULL;
		fbuf->next = NULL;
		free(fbuf);
	}
	else if (fbuf->next == NULL)
	{
		fbuf->previous->next = NULL;
		fbuf->previous = NULL;
		free(fbuf);
	}
	else
	{
		fbuf->previous->next = fbuf->next;
		fbuf->next->previous = fbuf->previous;
		fbuf->previous = NULL;
		fbuf->next = NULL;
		free(fbuf);
	}
	return (ret);
}

void	read_fd(t_gnl *fbuf, char **line)
{
	fbuf->sz = read(fbuf->fd, fbuf->buf, BUFFER_SIZE);
	if (fbuf->sz < 0)
	{
		free(*line);
		*line = NULL;
	}
	if (fbuf->sz <= 0)
		return ;
	fbuf->buf[fbuf->sz] = '\0';
}

int		get_next_line(int fd, char **line)
{
	static	t_gnl	*head;
	t_gnl			*fbuf;

	fbuf = checklst_add(&head, fd);
	if (!fbuf)
		return (-1);
	*line = ft_strdup("");
	if (!*line)
		return (clear_node(&head, fbuf, -1));
	while (1)
	{
		if (!*fbuf->buf)
			read_fd(fbuf, line);
		if (fbuf->sz <= 0)
			return (clear_node(&head, fbuf, fbuf->sz));
		*line = ft_strjoin(*line, fbuf->buf);
		if (!*line)
			return (clear_node(&head, fbuf, -1));
		if (eol_check(fbuf->buf))
		{
			prep_buf(fbuf->buf);
			return (1);
		}
		fbuf->buf[0] = '\0';
	}
}
