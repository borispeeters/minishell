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
		write(1, "minishell-0.1$ ", 15);
	}
}

void	free_shell(char **line, t_list **tokens)
{
	free(*line);
	*line = NULL;
	ft_lstclear(tokens, free_content);
	*tokens = NULL;
}

static void	print_env(t_env *env)
{
	int	i;

	i = 0;
	while (i < env->length)
	{
		printf("%s\n", env->vars[i]);
		++i;
	}
}

int		main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*line;
	int		status;
	t_list	*tokens;
	char	prompt[] = "minishell-0.1$ ";
	t_list	*table;

	init_env(&env, envp);
	print_env(&env);
	printf("BLOCK: [%d]\n", env.block_amount);
	resize_up_env(&env, ft_strdup("TAART=taart"));
	printf("BLOCK: [%d]\n", env.block_amount);
	resize_up_env(&env, ft_strdup("CAKE=cake"));
	printf("BLOCK: [%d]\n", env.block_amount);
	resize_up_env(&env, ft_strdup("RANJA=ranja"));
	printf("BLOCK: [%d]\n", env.block_amount);
	resize_up_env(&env, ft_strdup("CITROEN=citroen"));
	printf("BLOCK: [%d]\n", env.block_amount);
	resize_up_env(&env, ft_strdup("SPERZIEBONEN=sperziebonen"));
	printf("BLOCK: [%d]\n", env.block_amount);
	resize_up_env(&env, ft_strdup("POEP=poep"));
	printf("BLOCK: [%d]\n", env.block_amount);
	print_env(&env);
	line = NULL;
	(void)argc;
	(void)argv;
	status = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (status)
	{
		write(1, prompt, ft_strlen(prompt));
		status = get_next_line(0, &line);
		tokens = lexer(line);
		if (tokens != NULL && verify_syntax(tokens) == 0)
		{
			// print_list(tokens);
			while (tokens != NULL)
			{
				table = parse(&tokens);
				execute(table, &env);
			}
		}
		free_shell(&line, &tokens);
	}
	free_env(&env);
	write(1, "exit\n", 5);
	// system("leaks minishell");
	return (0);
}
