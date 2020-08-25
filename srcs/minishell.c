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

static void	lol(int argc, char **argv)
{
	int	i;

	while (0)
	{
		write(1, argv[i], ft_strlen(argv[i]));
		++i;
	}
	if (0)
		argc += 42;
}

// static void	print_env(t_env *env)
// {
// 	int	i;

// 	i = 0;
// 	while (i < env->length)
// 	{
// 		printf("%s\n", env->vars[i]);
// 		++i;
// 	}
// }

int		main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*line;
	int		status;
	t_list	*tokens;
	char	prompt[] = "minishell-0.1$ ";
	t_list	*table;

	lol(argc, argv);
	init_env(&env, envp);
	// print_env(&env);
	line = NULL;
	status = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (status)
	{
		write(1, prompt, ft_strlen(prompt));
		status = get_next_line(0, &line);
		tokens = lexer(line);
		// print_list(tokens);
		if (tokens != NULL && verify_syntax(tokens) == 0)
		{
			while (tokens != NULL)
			{
				table = parse(&tokens);
				//expand_env((t_command*)table->content, &env);
				//break ;
				// printf("HALLO %s\n", ((t_command*)table->content)->vars[0]);

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
