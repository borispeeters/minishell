#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <unistd.h>

# include <stdio.h> //

typedef struct	s_shell
{
	int				status;
	unsigned char	exit_status;
}				t_shell;

/*
**	Enum for the different types of redirect.
*/

typedef enum	e_redirect
{
	NO_REDIRECT,
	REDIRECT_IN,
	REDIRECT_OUT_TRUNC,
	REDIRECT_OUT_APPEND
}				t_redirect;

/*
**	Enum for the different types of command separators.
*/

typedef enum	e_separator
{
	NO_SEPARATOR,
	SEMICOLON,
	PIPE
}				t_separator;

/*
**	Struct for the parser.
*/

typedef struct	s_parser
{
	t_list		*start;
	t_separator	sep;
	t_separator	prev_sep;
}				t_parser;

/*
**	Enum for the different pipe options.
*/

typedef enum	e_pipe
{
	PIPE_NONE,
	PIPE_IN,
	PIPE_OUT,
	PIPE_BOTH
}				t_pipe;

/*
**	Struct to hold all necessary information about commands to be executed.
*/

typedef struct	s_command
{
	char		**vars;
	t_list		*files_in;
	int			fd_in;
	t_list		*files_out;
	int			fd_out;
	t_list		*out_modes;
	t_pipe		pipe;
}				t_command;

/*
**	Struct to hold all information necessary for the executor.
*/

typedef struct	s_executor
{
	pid_t		pid;
	char		**vars;
	char		*command;
	int			fd[2];
	int			in;
}				t_executor;

/*
**	Enum for different file open modes.
*/

typedef enum	e_filemode
{
	APPEND,
	TRUNC
}				t_filemode;

/*
**	Enum for different token states in the lexer.
*/

typedef enum	e_token
{
	INACTIVE,
	ACTIVE,
	META
}				t_token;

/*
**	Enum for different quote states in the lexer.
*/

typedef enum	e_quote
{
	NO_QUOTE,
	SNGL_QUOTE,
	DBL_QUOTE
}				t_quote;

/*
**	Enum for escapes.
*/

typedef enum	e_escape
{
	NO_ESCAPE,
	ESCAPE
}				t_escape;

/*
**	Struct to hold important information for the lexer.
*/

typedef struct	s_lexer
{
	t_quote		quote;
	char		*token_start;
	int			token_len;
	t_token		token_active;
	t_escape	escape;
}				t_lexer;

/*
**	Struct to hold information about the expansion process.
*/

typedef struct	s_expansion
{
	t_quote		quote;
	t_escape	escape;
}				t_expansion;

/*
**	Struct to hold information about finding paths for executables.
*/

typedef struct	s_path
{
	char		*path;
	char		**path_dirs;
	char		*abs;
}				t_path;

/*
**	Struct to hold information about environment variables.
*/

typedef struct	s_env
{
	char		**vars;
	int			length;
	int			block_size;
	int			block_amount;
}				t_env;

/*
**	lexer/lexer.c
*/

int				add_new_token(t_lexer *lex, t_list **head);
t_list			*lexer(char *line);

/*
**	lexer/lexer_states.c
*/

void			double_quote(t_lexer *lex, char *line);
void			single_quote(t_lexer *lex, char *line);
int				in_token(t_lexer *lex, char *line, t_list **head);
void			out_of_token(t_lexer *lex, char *line);
int				meta_encounter(t_lexer *lex, char *line, t_list **head);
void			escape_char(t_lexer *lex, char *line);

/*
**	lexer/verify_syntax.c
*/

int				verify_syntax(t_list *token);

/*
**	utils/array_utils.c
*/

char			**malloc_var_array(int n);
void			free_var_array(char **array);

/*
**	utils/command_utils.c
*/

t_list			*prepare_command(int length);
void			free_command(t_command *command);

/*
**	utils/env.c
*/

void			init_env(t_env *env, char **envp);
void			free_env(t_env *env);
void			resize_up_env(t_env *env, char *new);
void			resize_down_env(t_env *env, int remove);

/*
**	utils/error_utils.c
*/

void			shell_error(char *message);
void			shell_error_param(char *message, char *param);

/*
**	utils/shell_utils.c
*/

void			free_content(void *content);
int				is_space(int c);
int				is_metacharacter(int c);
t_separator		is_separator(char *token);
t_redirect		is_redirect(char *token);

/*
**	parser/parse.c
*/

t_list			*parse(t_list **tokens);
int				validate_command(t_parser *parser);
void			create_command(t_list **table, t_parser *parser);
void			parse_command(t_command *command, t_parser *parser);
void			handle_redirect(t_command *command, t_parser *parser,
					t_redirect redirect);

/*
**	parser/expand_env.c
*/

void			expand_env(t_shell *shell, t_command *cmd, t_env *env);

/*
**	parser/quote_removal.c
*/

void			quote_removal(t_command *cmd);

/*
**	executor/execute_loop.c
*/

void			execute(t_list *table, t_env *env);

/*
**	executor/search_path.c
*/

char			*search_path(char *cmd, char **env);

/*
**	executor/redirections.h
*/

int				output_redir(t_command *cmd);
int				input_redir(t_command *cmd);

/*
**	utils/expansion_utils.c
*/

int				is_env(int c);
void			exp_escape_char(t_expansion *exp);
void			exp_double_quote(t_expansion *exp);
void			exp_single_quote(t_expansion *exp);

/*
**	parser/quote_removal_states.c
*/

int				qr_single_quote(t_expansion *exp, char **vars, int i);
int				qr_double_quote(t_expansion *exp, char **vars, int i);
int				qr_escape(t_expansion *exp, char **vars, int i);

/*
**	parser/replace_env.c
*/

int				found_env(t_env *env, char **vars, int i);
void			str_replace(char **str, int index, int len, char *replace);

/*
**	utils/get_env.c
*/

char			*get_env(t_env *env, char *key);
int				get_env_index(t_env *env, char *key);
void			set_env(t_env *env, char *key, char *value);
void			free_pair(char **pair);

/*
**	builtins/builtin_exit.c
*/

void			builtin_exit(t_shell *shell, char **vars);

/*
**	builtins/builtin_env.c
*/

void			builtin_env(t_env *env);

/*
**	builtins/builtin_pwd.c
*/

void			builtin_pwd(t_shell *shell);

/*
**	builtins/builtin_cd.c
*/

void			builtin_cd(t_shell *shell, t_env *env, char **vars);

/*
**	builtins/builtin_echo.c
*/

void			builtin_echo(t_shell *shell, char **vars);

#endif
