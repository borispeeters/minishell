#include "minishell.h"

static void	reset_array(char **array, int c)
{
	int	i;
	int	j;

	i = 0;
	while (array[i])
	{
		j = 0;
		while (array[i][j])
		{
			if (array[i][j] == c - 42)
				array[i][j] = c;
			++j;
		}
		++i;
	}
}

static void	split_insert(t_command *cmd, int i, int c)
{
	char	**split;

	// printf("split_insert cmd->vars[%d]: [%s]\n", i, cmd->vars[i]);
	if (cmd->vars[i] == NULL)
		return ;
	split = ft_split(cmd->vars[i], c);
	if (split == NULL)
		shell_error_malloc();
	reset_array(split, c);
	reset_array(cmd->vars, c);
	realloc_vars(cmd, split, i);
	free_var_array(split);
}

static void	split_loop(t_command *cmd, t_expansion *exp, int i)
{
	int	j;

	j = 0;
	while (cmd->vars[i][j])
	{
		exp_quote_handler(exp, cmd->vars[i][j]);
		if (is_space(cmd->vars[i][j]) && (exp->escape == ESCAPE ||
		exp->quote != NO_QUOTE))
			cmd->vars[i][j] -= 42;
		if (exp->escape == ESCAPE && cmd->vars[i][j] != '\\')
			exp->escape = NO_ESCAPE;
		++j;
	}
}

void		split_words(t_command *cmd)
{
	t_expansion	exp;
	char		*tmp;
	int			i;

	i = 0;
	while (cmd->vars[i])
	{
		exp.quote = NO_QUOTE;
		exp.escape = NO_ESCAPE;
		tmp = ft_strtrim(cmd->vars[i], " \t\n");
		free(cmd->vars[i]);
		if (tmp == NULL)
			shell_error_malloc();
		cmd->vars[i] = tmp;
		split_loop(cmd, &exp, i);
		split_insert(cmd, i, '\t');
		split_insert(cmd, i, ' ');
		if (cmd->vars[i])
			++i;
	}
}
