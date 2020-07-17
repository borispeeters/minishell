#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

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

t_list	*lexer(char *line);
int		add_new_token(t_lexer *lex, t_list **head);
void	double_quote(t_lexer *lex, char *line);
void	single_quote(t_lexer *lex, char *line);
int		in_token(t_lexer *lex, char *line, t_list **head);
void	out_of_token(t_lexer *lex, char *line);
int		meta_encounter(t_lexer *lex, char *line, t_list **head);
void	free_content(void *content);
int		is_space(int c);
int		is_metacharacter(int c);
void	parse(t_list *tokens);

#endif
