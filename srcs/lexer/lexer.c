#include <unistd.h>
#include "libft.h"
#include "minishell.h"

int		add_new_token(t_lexer *lex, t_list **head)
{
	char	*token;
	t_list	*node;

	token = ft_substr(lex->token_start, 0, lex->token_len);
	if (token == NULL)
		return (-1);
	node = ft_lstnew(token);
	if (node == NULL)
	{
		free(token);
		return (-1);
	}
	ft_lstadd_back(head, node);
	return (0);
}

int		lex_loop(t_lexer *lex, char *line, t_list **head)
{
	int	ret;

	ret = 0;
	if (*line == '\"' && lex->quote != SNGL_QUOTE)
		double_quote(lex, line);
	else if (*line == '\'' && lex->quote != DBL_QUOTE)
		single_quote(lex, line);
	if (lex->token_active == ACTIVE && lex->quote == NO_QUOTE)
		ret = in_token(lex, line, head);
	else if (lex->token_active == INACTIVE)
		out_of_token(lex, line);
	else if (lex->token_active == META && lex->quote == NO_QUOTE)
		ret = meta_encounter(lex, line, head);
	if (lex->token_active >= ACTIVE)
		++lex->token_len;
	return (ret);
}

t_list	*lexer(char *line)
{
	t_list	*head;
	t_lexer	lex;

	head = NULL;
	lex.quote = NO_QUOTE;
	lex.token_start = NULL;
	lex.token_len = 0;
	lex.token_active = INACTIVE;
	while (*line)
	{
		if (lex_loop(&lex, line, &head) == -1)
		{
			ft_lstclear(&head, free_content);
			return (NULL);
		}
		++line;
	}
	if (lex.token_active >= ACTIVE)
		if (add_new_token(&lex, &head) == -1)
		{
			ft_lstclear(&head, free_content);
			return (NULL);
		}
	if (lex.quote != NO_QUOTE)
	{
		write(1, "minishell: multiline commands are not supported\n", 48);
		ft_lstclear(&head, free_content);
		return (NULL);
	}
	return (head);
}
