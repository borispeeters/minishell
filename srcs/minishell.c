#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

void	write_prompt(t_shell *shell)
{
	char	*name;

	name = ft_strrchr(shell->name, '/');
	if (name != NULL)
		name += 1;
	else
		name = shell->name;
	write(1, name, ft_strlen(name));
	write(1, "-0.1$ ", 6);
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

void	signal_handler(int sig)
{
	signal(sig, signal_handler);
	if (sig == SIGINT)
	{
		write(1, "\b\b  \n", 5);
		write(1, "minishell-0.1$ ", 15);
	}
	if (sig == SIGQUIT)
	{
		write(1, "\b\b  \b\b", 6);
	}
}

void	free_shell(char **line, t_list **tokens)
{
	free(*line);
	*line = NULL;
	ft_lstclear(tokens, free_content);
	*tokens = NULL;
}

int		main(int argc, char **argv, char **envp)
{
	t_env	env;
	char	*line;
	t_list	*tokens;
	t_list	*table;
	t_shell	shell;

	if (argc > 1)
	{
		write(2, "Scripting is not supported\n", 27);
		return (1);
	}
	shell.name = argv[0];
	init_env(&env, envp);
	line = NULL;
	shell.status = 1;
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	while (shell.status)
	{
		write_prompt(&shell);
		shell.status = get_next_line(0, &line);
		tokens = lexer(line);
		// print_list(tokens);
		if (tokens != NULL && verify_syntax(tokens) == 0)
		{
			while (shell.status && tokens != NULL)
			{
				shell.exit_status = 0;
				table = parse(&tokens);
<<<<<<< HEAD
				//expand_env((t_command*)table->content, &env);
				//break ;
=======
				expand_env((t_command*)table->content, &env);
				quote_removal((t_command*)table->content);
				// break ;
>>>>>>> boris
				// printf("HALLO %s\n", ((t_command*)table->content)->vars[0]);

				execute(table, &env);
			}
		}
		free_shell(&line, &tokens);
	}
	free_env(&env);
	write(1, "exit\n", 5);
	printf("exit status: %d\n", shell.exit_status);
	// system("leaks minishell");
	return (shell.exit_status);
}
