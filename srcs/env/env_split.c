#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	Helper function that frees allocated memory then exits.
*/

void	free_pair_exit(char **pair)
{
	free(pair[0]);
	free(pair[1]);
	free(pair);
	shell_error_malloc();
}

/*
**	This function will split an environment variable in the environment list
**	into a key-value pair by looking for the first '=' character.
*/

char	**env_split(char const *s)
{
	char	**pair;
	char	*sep;

	if (s == NULL)
		return (NULL);
	pair = ft_calloc(3, sizeof(*pair));
	if (pair == NULL)
		shell_error_malloc();
	sep = ft_strchr(s, '=');
	if (sep == NULL)
	{
		pair[0] = ft_strdup(s);
		if (pair[0] == NULL)
			free_pair_exit(pair);
		return (pair);
	}
	pair[0] = ft_substr(s, 0, sep - s);
	pair[1] = ft_strdup(sep + 1);
	if (pair[0] == NULL || pair[1] == NULL)
		free_pair_exit(pair);
	return (pair);
}
