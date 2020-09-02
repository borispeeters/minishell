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
}

void	free_command_table(t_list **table)
{
	t_list		*node;
	t_command	*cmd;

	node = *table;
	while (node)
	{
		cmd = node->content;
		ft_lstclear(&cmd->files_in, free_content);
		ft_lstclear(&cmd->files_out, free_content);
		ft_lstclear(&cmd->out_modes, free_content);
		free_var_array(cmd->vars);
		node = node->next;
	}
	ft_lstclear(table, free_content);
}

void	clear_screen()
{
	ft_putstr_fd("\e[1;1H\e[2J", STDOUT_FILENO);
}

void	init_builtins(t_shell *shell)
{
	shell->builtin[0] = builtin_cd;
	shell->builtin[1] = builtin_echo;
	shell->builtin[2] = builtin_env;
	shell->builtin[3] = builtin_exit;
	shell->builtin[4] = builtin_export;
	shell->builtin[5] = builtin_pwd;
	shell->builtin[6] = builtin_unset;
	ft_strlcpy(shell->b_name[0], "cd", 3);
	ft_strlcpy(shell->b_name[1], "echo", 5);
	ft_strlcpy(shell->b_name[2], "env", 4);
	ft_strlcpy(shell->b_name[3], "exit", 5);
	ft_strlcpy(shell->b_name[4], "export", 7);
	ft_strlcpy(shell->b_name[5], "pwd", 4);
	ft_strlcpy(shell->b_name[6], "unset", 6);
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
	// clear_screen();
	(void)argv;
	init_env(&env, envp);
	init_builtins(&shell);

	line = NULL;
	shell.status = 1;
	while (shell.status)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		write(1, "minishell-0.1$ ", 15);
		shell.status = get_next_line(0, &line);
		tokens = lexer(line);
		// print_list(tokens);
		if (tokens != NULL && verify_syntax(tokens) == 0)
		{
			while (shell.status && tokens != NULL)
			{
				table = parse(&tokens);
				expand_env(&shell, (t_command*)table->content, &env);
				quote_removal((t_command*)table->content);
				shell.exit_status = 0;
				execute_loop(&shell, table, &env);
				free_command_table(&table);
			}
		}
		free_shell(&line, &tokens);
	}
	free_env(&env);
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (shell.exit_status);
}
