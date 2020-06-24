# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/11 00:50:41 by bpeeters       #+#    #+#                 #
#    Updated: 2020/03/11 22:39:53 by bpeeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = main.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIB = lib

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIB)
	@cp lib/libftprintf.a ./libftprintf.a
	@$(CC) $(OBJ) libftprintf.a -o $(NAME)

test: all
	@./minishell

%.o: %.c
	@printf "Compiling $?\n"
	@$(CC) $(CFLAGS) -c $? -o $@

clean:
	@$(RM) $(OBJ)
	@$(RM) libftprintf.a
	@make clean -C $(LIB)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIB)

re: fclean all
