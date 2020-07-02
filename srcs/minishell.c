/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:48:06 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/02 19:30:41 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>//
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

int		isspace(int c)
{
	return (c == ' ' || c == '	');
}

int		is_metacharacter(int c)
{
	char	metachar[12];
	int		i;

	ft_strlcpy(metachar, " \t\n|;()<>", 11);
	i = 0;
	while (metachar[i])
	{
		if (c == metachar[i])
			return (1);
		++i;
	}
	return (0);
}

t_lexer	*lexer(char *line)
{
	t_list	*head;
	t_quote	quote;
	char	*token_start;
	int		token_len;
	t_bool	token_active;

	head = NULL;
	quote = NO_QUOTE;
	token_start = NULL;
	token_len = 1;
	token_active = FALSE;
	while (*line)
	{
		if (quote != NO_QUOTE || !isspace(*line))
		{
			if (*line == '\"' && quote != SNGL_QUOTE)
			{
				if (quote == DBL_QUOTE)
					quote = NO_QUOTE;
				else if (quote == NO_QUOTE)
				{
					quote = DBL_QUOTE;
					if (token_active == FALSE)
					{
						token_active = TRUE;
						token_start = line;
						token_len = 1;
					}
				}
			}
			else if (*line == '\'' && quote != DBL_QUOTE)
			{
				if (quote == SNGL_QUOTE)
					quote = NO_QUOTE;
				else if (quote == NO_QUOTE)
				{
					quote = SNGL_QUOTE;
					if (token_active == FALSE)
					{
						token_active = TRUE;
						token_start = line;
						token_len = 1;
					}
				}
			}
			else
			{
				if (token_active == TRUE)
				{
					if (is_metacharacter(*line))
					{
						ft_lstadd_back(&head, ft_lstnew(ft_substr(token_start, 0, token_len)));
						token_start = line;
						token_len = 1;
					}
				}
			}
		}
		if (token_active == TRUE)
			++token_len;
		++line;
	}
	return NULL;
}

void	print_list(t_lexer *node)
{
	while (node)
	{
		write(1, node->token, ft_strlen(node->token));
		node = node->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char	*line;
	int		status;
	t_lexer	*tokens;

	char	prompt[] = "minishell> ";

	status = 1;
	while (status)
	{
		write(1, prompt, ft_strlen(prompt));
		status = get_next_line(0, &line);
		tokens = lexer(line);
		print_list(tokens);
	}
	return (0);
}
