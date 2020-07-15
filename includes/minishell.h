/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 14:04:34 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/15 14:16:12 by mpeerdem      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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
	int			length;
	int			redirects;
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

/*
**	lexer/lexer.c
*/

t_list			*lexer(char *line);

/*
**	lexer/lexer_states.c
*/

void			double_quote(t_lexer *lex, char *line);
void			single_quote(t_lexer *lex, char *line);
void			in_token(t_lexer *lex, char *line, t_list **head);
void			out_of_token(t_lexer *lex, char *line);
void			meta_encounter(t_lexer *lex, char *line, t_list **head);

/*
**	utils/array_utils.c
*/

char			**malloc_var_array(int n);
void			free_var_array(char **array);

/*
**	utils/command_utils.c
*/

t_command		*prepare_command(t_parser *parser, int length);
void			free_command(t_command *command);

/*
**	utils/shell_utils.c
*/

int				is_space(int c);
int				is_metacharacter(int c);
t_separator		is_separator(char *token);
t_redirect		is_redirect(char *token);

/*
**	parser/parse.c
*/

void			parse(t_list *tokens);
void			parse_metacharacter(t_parser *parser, char *token);
int				validate_command(t_parser *parser);
void			make_command(t_list **table, t_parser *parser);

#endif
