/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_redirect.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:01 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:02 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

/*
**	This helper function will try to create a new link in a list, and
**	print an error if malloc failed.
*/

static void	try_add_list(t_list **list, void *content)
{
	t_list		*new_link;

	new_link = ft_lstnew(content);
	if (new_link == NULL)
		shell_error_malloc();
	ft_lstadd_back(list, new_link);
}

/*
**	This function will handle a redirect, and put the right information in the
**	struct.
*/

void		handle_redirect(t_command *command, t_parser *parser,
				t_redirect redirect)
{
	char		*file;
	t_filemode	*mode;
	t_list		*tmp;

	file = (char *)parser->start->next->content;
	if (redirect == REDIRECT_IN)
		try_add_list(&(command->files_in), file);
	else
	{
		mode = malloc(sizeof(t_filemode));
		if (mode == NULL)
			shell_error_malloc();
		*mode = (redirect == REDIRECT_OUT_TRUNC) ? TRUNC : APPEND;
		try_add_list(&(command->files_out), file);
		try_add_list(&(command->out_modes), mode);
	}
	tmp = parser->start;
	parser->start = parser->start->next;
	free(tmp->content);
	free(tmp);
}
