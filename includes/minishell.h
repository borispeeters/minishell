/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <bpeeters@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/03/11 14:04:34 by bpeeters      #+#    #+#                 */
/*   Updated: 2020/07/03 14:55:55 by bpeeters      ########   odam.nl         */
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

typedef struct		s_lexer
{
	char			*token;
	struct s_lexer	*next;
}					t_lexer;


#endif
