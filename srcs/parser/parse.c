/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 11:02:36 by mpeerdem      #+#    #+#                 */
/*   Updated: 2020/07/13 11:08:17 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft.h"
#include <stdio.h>//

void		parse(t_list *tokens)
{
	int		i;
	char	*token;

	i = 1;
	while (tokens != NULL)
	{
		token = (char *)tokens->content;
		printf("Token %i: %s.\n", i, token);
		i++;
		tokens = tokens->next;
	}
}
