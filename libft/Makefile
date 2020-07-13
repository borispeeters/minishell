# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: mpeerdem <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/10/29 11:58:29 by mpeerdem      #+#    #+#                  #
#    Updated: 2020/07/13 09:29:27 by mpeerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		libft.a
HEADER =	libft.h
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
_OBJS =		ft_memset ft_bzero ft_memcpy ft_memccpy ft_memmove \
			ft_memchr ft_memcmp ft_strlen ft_strlcpy ft_strlcat \
			ft_strchr ft_strrchr ft_strnstr ft_strncmp ft_atoi \
			ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
			ft_toupper ft_tolower ft_calloc ft_strdup ft_substr \
			ft_strjoin ft_strtrim ft_split ft_itoa ft_strmapi \
			ft_putchar_fd ft_putstr_fd ft_putendl_fd ft_putnbr_fd \
			get_next_line get_next_line_utils ft_strcmp ft_isnumber \
			ft_removechar ft_array_is_square \
			ft_lstnew ft_lstadd_front ft_lstsize \
			ft_lstlast ft_lstadd_back ft_lstdelone \
			ft_lstclear ft_lstiter ft_lstmap
OBJS =		$(addsuffix .o, $(_OBJS))

all: $(NAME)

.PHONY: all clean fclean re

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $? -o $@ -I.

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
