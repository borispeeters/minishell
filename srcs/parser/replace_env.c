/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   replace_env.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:09 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/16 14:22:09 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will replace a subsection of str with replace.
*/

int			str_replace(char **str, int index, int len, char *replace)
{
	char	*tmp;
	int		new_len;
	int		quotes;

	quotes = count_quote_escape(replace);
	new_len = ft_strlen(*str) - len + ft_strlen(replace);
	tmp = malloc(sizeof(*tmp) * (new_len + quotes + 1));
	if (tmp == NULL)
		shell_error_malloc();
	ft_strlcpy(tmp, *str, index + 1);
	ft_strlcat(tmp, replace, ft_strlen(tmp) + ft_strlen(replace) + 1);
	ft_strlcat(tmp, *str + index + len, new_len + 1);
	escape_quotes(tmp);
	free(*str);
	*str = tmp;
	return (ft_strlen(replace) + quotes);
}

/*
**	This function will return the length of an environment variable
**	before it is expanded.
*/

static int	env_len(char *env)
{
	int	len;

	len = 1;
	if (!(ft_isalpha(env[len]) || env[len] == '_'))
	{
		++len;
		return (len);
	}
	while (env[len] && (ft_isalnum(env[len]) || env[len] == '_'))
	{
		++len;
	}
	return (len);
}

/*
**	This function will replace an environment variable when it is found.
*/

int			found_env(t_env *env, char **vars, int i)
{
	int		len;
	char	*value;
	char	*key;

	len = env_len(*vars + i);
	key = ft_substr(*vars, i + 1, len - 1);
	if (key == NULL)
		shell_error_malloc();
	value = get_env(env, key);
	free(key);
	if (value == NULL)
		shell_error_malloc();
	len = str_replace(vars, i, len, value);
	free(value);
	return (len);
}
