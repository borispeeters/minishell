/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: bpeeters <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/21 14:26:15 by bpeeters       #+#    #+#                */
/*   Updated: 2020/03/10 20:11:28 by bpeeters      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 128
# endif

# include <unistd.h>

typedef	struct		s_gnl
{
	int				fd;
	char			buf[BUFFER_SIZE + 1];
	ssize_t			sz;
	struct s_gnl	*next;
	struct s_gnl	*previous;
}					t_gnl;

int					get_next_line(int fd, char **line);
void				prep_buf(char *buf);
size_t				line_len(const char *s);
int					eol_check(char *str);
char				*ft_strjoin(const char *s1, const char *s2);
char				*ft_strdup(const char *s1);

#endif
