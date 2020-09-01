#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will check
**	if the command line doesn't begin with the `;' token.
*/

static int	check_first_sep(char *str)
{
	if (*str == ';')
	{
		shell_error_syntax(str);
		return (1);
	}
	return (0);
}

/*
**	This function will verify that the syntax is correct.
**	If it isn't it will print an error message.
*/

int			verify_syntax(t_list *token)
{
	char	*str;
	t_token	token_active;

	if (check_first_sep((char*)token->content))
		return (1);
	token_active = INACTIVE;
	while (token)
	{
		str = (char*)token->content;
		if (is_metacharacter(str[0]))
		{
			if (ft_strncmp(str, ">>>", 3) == 0 || token_active == META)
			{
				shell_error_syntax(str);
				return (1);
			}
			token_active = META;
		}
		else if (token_active == META)
			token_active = INACTIVE;
		token = token->next;
	}
	return (0);
}
