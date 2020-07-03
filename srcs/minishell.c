/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:48:06 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/03 15:03:18 by bpeeters      ########   odam.nl         */
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

t_list	*lexer(char *line)
{
	t_list	*head;
	t_quote	quote;
	char	*token_start;
	int		token_len;
	t_token	token_active;

	head = NULL;
	quote = NO_QUOTE;
	token_start = NULL;
	token_len = 0;
	token_active = INACTIVE;
	while (*line)
	{
		if (*line == '\"' && quote != SNGL_QUOTE)
		{
			if (quote == DBL_QUOTE)
				quote = NO_QUOTE;
			else if (quote == NO_QUOTE)
			{
				quote = DBL_QUOTE;
				if (token_active == INACTIVE)
				{
					token_active = ACTIVE;
					token_start = line;
					token_len = 0;
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
				if (token_active == INACTIVE)
				{
					token_active = ACTIVE;
					token_start = line;
					token_len = 0;
				}
			}
		}
		if (token_active == ACTIVE && quote == NO_QUOTE)
		{
			if (is_metacharacter(*line))
			{
				ft_lstadd_back(&head, ft_lstnew(ft_substr(token_start, 0, token_len)));
				token_start = line;
				token_len = 0;
				token_active = META;
			}
			if (isspace(*line) && quote == NO_QUOTE)
				token_active = INACTIVE;
		}
		else if (token_active == INACTIVE)
		{
			if (!isspace(*line))
			{
				token_start = line;
				token_len = 0;
				token_active = ACTIVE;
			}
		}
		else if (token_active == META)
		{
			ft_lstadd_back(&head, ft_lstnew(ft_substr(token_start, 0, token_len)));
			token_start = line;
			token_len = 0;
			token_active = ACTIVE;
		}
		if (token_active >= ACTIVE)
			++token_len;
		++line;
	}
	if (token_active >= ACTIVE)
		ft_lstadd_back(&head, ft_lstnew(ft_substr(token_start, 0, token_len)));
	return (head);
}

void	print_list(t_list *node)
{
	write(1, "_____START TOKENS________\n\n", 27);
	while (node)
	{
		write(1, "[", 1);
		write(1, node->content, ft_strlen(node->content));
		write(1, "]", 1);
		write(1, "\n", 1);
		node = node->next;
	}
	write(1, "\n_____END TOKENS__________\n\n", 27);
}

int	main(int argc, char **argv, char **envp)
{
	(void)argc;
	(void)argv;
	(void)envp;

	char	*line;
	int		status;
	t_list	*tokens;

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
