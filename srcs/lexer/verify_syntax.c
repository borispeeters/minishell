#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	This function will verify that the syntax is correct.
**	If it isn't it will print an error message.
*/

int			verify_syntax(t_list *token)
{
	char	*str;
	t_token	token_active;

	token_active = INACTIVE;
	while (token)
	{
		str = (char*)token->content;
		if (is_metacharacter(str[0]))
		{
			if ((str[0] == '>' && ft_strcmp(str, ">") && ft_strcmp(str, ">>"))
				|| token_active == META)
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
