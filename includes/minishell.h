/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 14:04:34 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/07 11:13:10 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
int		isspace(int c);
int		is_metacharacter(int c);

#endif
