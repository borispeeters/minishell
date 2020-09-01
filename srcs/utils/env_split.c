#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

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
		return (pair);
	}
	pair[0] = ft_substr(s, 0, sep - s);
	pair[1] = ft_strdup(sep + 1);
	return (pair);
}
