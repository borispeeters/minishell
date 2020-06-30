/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 11:55:46 by mpeerdem      #+#    #+#                 */
/*   Updated: 2019/11/07 15:29:40 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list		*new_begin;
	t_list		*new_item;
	t_list		*previous;
	void		*new_content;

	new_begin = NULL;
	while (lst)
	{
		new_content = (*f)(lst->content);
		new_item = ft_lstnew(new_content);
		if (new_item == NULL)
		{
			ft_lstclear(&new_begin, del);
			return (NULL);
		}
		if (new_begin == NULL)
			new_begin = new_item;
		else
			previous->next = new_item;
		previous = new_item;
		new_item = lst->next;
		lst = new_item;
	}
	return (new_begin);
}
