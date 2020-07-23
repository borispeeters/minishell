#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

# include <stdio.h> //

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
**	Struct to hold all necessary information to be able to execute commands.
*/

typedef struct	s_command
{
	char		**vars;
	t_list		*files_in;
	t_list		*files_out;
	t_list		*out_modes;
	t_pipe		pipe;
}				t_command;

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
**	Struct to hold important information for the lexer.
*/

typedef struct	s_lexer
{
	t_quote		quote;
	char		*token_start;
	int			token_len;
	t_token		token_active;
}				t_lexer;

typedef struct	s_expansion 
{
	t_quote		quote;
	char		*env_start;
	int			env_len;
	char		*env;
}				t_expansion;


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

char			**init_env(char **envp);
char			**free_env(char **env);

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

t_list			*parse(t_list *tokens);
int				validate_command(t_parser *parser);
void			create_command(t_list **table, t_parser *parser);
void			parse_command(t_command *command, t_parser *parser);
void			handle_redirect(t_command *command, t_parser *parser,
					t_redirect redirect);
void			expand_env(char **str, char **env);

/*
**	executor/execute_loop.c
*/

void			execute(t_list *table, char **env);


#endif
