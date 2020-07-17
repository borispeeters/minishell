/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:48:06 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/17 17:39:36 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

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

void	signal_handler(int sig)
{
	signal(sig, signal_handler);
	if (sig == SIGINT)
	{
		write(1, "\b\b  \n", 5);
		write(1, "minishell> ", 11);
	}
}

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	t_list	*tokens;
	char	prompt[] = "minishell> ";

	line = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	status = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (status)
	{
		write(1, prompt, ft_strlen(prompt));
		status = get_next_line(0, &line);
		tokens = lexer(line);
		// print_list(tokens);
		// parse(tokens);
		free(line);
		line = NULL;
		ft_lstclear(&tokens, free_content);
	}
	write(1, "exit\n", 5);
	return (0);
}
