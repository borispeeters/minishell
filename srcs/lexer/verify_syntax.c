#include <unistd.h>
#include "libft.h"
#include "minishell.h"

int		verify_syntax(t_list *token)
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
				write(2, "minishell: syntax error near unexpected token `", 47);
				write(2, str, 1);
				write(2, "'\n", 2);
				return (-1);
			}
			token_active = META;
		}
		else if (token_active == META)
			token_active = INACTIVE;
		token = token->next;
	}
	return (0);
}
