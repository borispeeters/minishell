#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

static void	insert_split(t_command *cmd, char **split, char **tmp, int index)
{
	int	i;
	int	j;

	i = 0;
	while (i < index)
	{
		tmp[i] = ft_strdup(cmd->vars[i]);
		if (tmp[i] == NULL)
			shell_error_malloc();
		++i;
	}
	j = 0 - i;
	while (split[j + i])
	{
		tmp[i] = ft_strdup(split[j + i]);
		if (tmp[i] == NULL)
			shell_error_malloc();
		++i;
	}
	while (cmd->vars[i + 1 - arrlen(split)])
	{
		tmp[i] = ft_strdup(cmd->vars[i + 1 - arrlen(split)]);
		if (tmp[i] == NULL)
			shell_error_malloc();
		++i;
	}
}

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
