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

int		main(int argc, char **argv, char **envp)
{
	char	*line;
	int		status;
	t_list	*tokens;
	char	prompt[] = "minishell> ";

	(void)argc;
	(void)argv;
	(void)envp;
	status = 1;
	while (status)
	{
		write(1, prompt, ft_strlen(prompt));
		status = get_next_line(0, &line);
		tokens = lexer(line);
		print_list(tokens);
		parse(tokens);
	}
	return (0);
}
