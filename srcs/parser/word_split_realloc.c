/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   word_split_realloc.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:13 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/17 12:02:48 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	Inserts the original vars that came before the splitted words
**	into the new vars.
*/

static void	insert_pre_split(t_command *cmd, char **tmp, int *i, int end)
{
	while (*i < end)
	{
		tmp[*i] = ft_strdup(cmd->vars[*i]);
		if (tmp[*i] == NULL)
		{
			free_var_array(tmp);
			shell_error_malloc();
		}
		++(*i);
	}
}

/*
**	Inserts the splitted words into the new vars.
*/

static void	insert_at_split(char **split, char **tmp, int *i)
{
	int	j;

	j = 0 - *i;
	while (split[j + *i])
	{
		tmp[*i] = ft_strdup(split[j + *i]);
		if (tmp[*i] == NULL)
		{
			free_var_array(tmp);
			shell_error_malloc();
		}
		++(*i);
	}
}

/*
**	Inserts the original vars that came after the splitted words
**	into the new vars.
*/

static void	insert_post_split(t_command *cmd, char **tmp, int *i, int len)
{
	while (cmd->vars[*i + 1 - len])
	{
		tmp[*i] = ft_strdup(cmd->vars[*i + 1 - len]);
		if (tmp[*i] == NULL)
		{
			free_var_array(tmp);
			shell_error_malloc();
		}
		++(*i);
	}
}

/*
**	Delegates the insertion to three helper functions.
*/

static void	insert_split(t_command *cmd, char **split, char **tmp, int end)
{
	int	i;

	i = 0;
	insert_pre_split(cmd, tmp, &i, end);
	insert_at_split(split, tmp, &i);
	insert_post_split(cmd, tmp, &i, arrlen(split));
}

/*
**	Allocates the command arguments to make room for the splitted words.
*/

void		realloc_vars(t_command *cmd, char **split, int index)
{
	int		old_len;
	int		new_len;
	char	**tmp;

	old_len = arrlen(cmd->vars);
	new_len = old_len + arrlen(split) - 1;
	if (old_len == new_len)
		return ;
	tmp = malloc(sizeof(*tmp) * (new_len + 1));
	if (tmp == NULL)
		shell_error_malloc();
	if (new_len > 0)
	{
		insert_split(cmd, split, tmp, index);
	}
	tmp[new_len] = NULL;
	free_var_array(cmd->vars);
	cmd->vars = tmp;
}
