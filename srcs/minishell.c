/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/16 14:22:40 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/09/17 11:51:39 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <unistd.h>
#include "libft.h"
#include "minishell.h"

/*
**	Initializes some values for the builtins
**	so that they can later easily be called in a loop.
*/

static void	init_builtins(t_shell *shell)
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

/*
**	Function to loop through commands separated by the ';' token.
*/

static void	command_loop(t_shell *shell, t_list *tokens)
{
	t_list	*table;

	while (shell->status && tokens != NULL)
	{
		table = parse(&tokens);
		expand_env(shell, (t_command*)table->content);
		split_words((t_command*)table->content);
		quote_removal((t_command*)table->content);
		shell->exit_status = 0;
		execute_loop(shell, table);
		free_command_table(&table);
	}
}

/*
**	This function checks if the syntax is valid
**	and if it is goes to the command loop.
**	Otherwise updates the exit status and prints an error.
*/

static void	check_syntax(t_shell *shell, t_list *tokens)
{
	if (verify_syntax(tokens) != 0)
	{
		shell->exit_status = 258 % 256;
		ft_lstclear(&tokens, free_content);
		return ;
	}
	command_loop(shell, tokens);
}

/*
**	The main loop that waits for input
**	and then calls other functions to process it.
*/

static void	shell_loop(t_shell *shell)
{
	t_list	*tokens;
	char	*line;

	line = NULL;
	while (shell->status)
	{
		signal(SIGINT, signal_handler);
		signal(SIGQUIT, signal_handler);
		write_prompt();
		shell->status = get_next_line(0, &line);
		if (shell->status == -1)
		{
			shell_error("error reading input");
			shell->exit_status = 1;
			return ;
		}
		tokens = lexer(line);
		if (tokens != NULL)
			check_syntax(shell, tokens);
		free(line);
		line = NULL;
	}
}

/*
**	Main function that initializes some values, calls the main loop
**	then cleanly quits the program.
*/

int			main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	t_env	env;

	if (argc > 1)
	{
		shell_error("Scripting is not supported");
		return (1);
	}
	(void)argv;
	init_env(&env, envp);
	shell.env = &env;
	init_builtins(&shell);
	shell.status = 1;
	shell.exit_status = 0;
	shell_loop(&shell);
	free_env(shell.env);
	ft_putendl_fd("exit", STDOUT_FILENO);
	return (shell.exit_status);
}
