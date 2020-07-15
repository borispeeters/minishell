/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mpeerdem <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 14:04:34 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/15 14:32:50 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"

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
	char		*file_in;
	char		*file_out;
	t_pipe		pipe;
}				t_command;

typedef enum	e_token
{
	INACTIVE,
	ACTIVE,
	META
}				t_token;

typedef enum	e_quote
{
	NO_QUOTE,
	SNGL_QUOTE,
	DBL_QUOTE
}				t_quote;

typedef struct	s_lexer
{
	t_quote		quote;
	char		*token_start;
	int			token_len;
	t_token		token_active;
}				t_lexer;

t_list	*lexer(char *line);
void	double_quote(t_lexer *lex, char *line);
void	single_quote(t_lexer *lex, char *line);
void	in_token(t_lexer *lex, char *line, t_list **head);
void	out_of_token(t_lexer *lex, char *line);
void	meta_encounter(t_lexer *lex, char *line, t_list **head);
int		is_space(int c);
int		is_metacharacter(int c);
void	parse(t_list *tokens);

#endif
