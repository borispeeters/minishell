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
		shell_error("Scripting is not supported");
		return (1);
	}
	(void)argv;
	init_env(&env, envp);
	line = NULL;
	shell.status = 1;
	while (shell.status)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		write(1, "minishell-0.1$ ", 15);
		shell.exit_status = 0;
		shell.status = get_next_line(0, &line);
		tokens = lexer(line);
		// print_list(tokens);
		if (tokens != NULL && verify_syntax(tokens) == 0)
		{
			while (shell.status && tokens != NULL)
			{
				table = parse(&tokens);
				expand_env((t_command*)table->content, &env);
				quote_removal((t_command*)table->content);
				execute(table, &env);
			}
		}
		char	*tmp[4];
		tmp[0] = "cd";
		tmp[1] = "..";
		tmp[2] = "lol";
		tmp[3] = NULL;
		// builtin_pwd(&shell);
		// builtin_cd(&shell, &env, tmp);
		// builtin_pwd(&shell);
		free_shell(&line, &tokens);
	}
	free_env(&env);
	write(1, "exit\n", 5);
	printf("exit status: %d\n", shell.exit_status);
	// system("leaks minishell");
	return (shell.exit_status);
}
