/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/06/30 15:48:06 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/16 14:51:11 by bpeeters      ########   odam.nl         */
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

void	handle_sigint(int sig)
{
	signal(sig, handle_sigint);
	write(1, "\b\b  ", 4);
	write(1, "\nminishell> ", 12);
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
	while (status)
	{
		signal(SIGINT, handle_sigint);
		write(1, prompt, ft_strlen(prompt));
		status = get_next_line(0, &line);
		tokens = lexer(line);
		print_list(tokens);
		parse(tokens);
		free(line);
		line = NULL;
		ft_lstclear(&tokens, free_content);
		write(1, "AHAHAH\n", 7);
	}
	write(1, "exit\n", 5);
	return (0);
}
