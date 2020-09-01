#include <stdlib.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will print an error if an invalid environment variable
**	is given to export or unset.
*/

void		shell_error_env(char *s, char *param)
{
	char	*tmp;
	char	*msg;

	tmp = ft_strjoin("`", s);
	if (tmp == NULL)
		shell_error_malloc();
	msg = ft_strjoin(tmp, "\': not a valid identifier");
	if (msg != NULL)
	{
		shell_error_param(msg, param);
		free(msg);
	}
	free(tmp);
}
