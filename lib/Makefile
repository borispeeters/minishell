# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <marvin@codam.nl>                   +#+                      #
#                                                    +#+                       #
#    Created: 2019/12/10 12:37:45 by bpeeters       #+#    #+#                 #
#    Updated: 2020/03/11 16:05:44 by bpeeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a
SRC = ft_checks.c ft_lengths.c ft_print1.c ft_print2.c ft_printf.c \
	   ft_putchar_error.c libft_reject.c putstuff_fd.c
OBJ = $(SRC:.c=.o)
CFLAGS = -Wall -Wextra -Werror
LIBFT = libft

.PHONY: clean fclean

all: $(NAME)

$(NAME): $(OBJ)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rcs $(NAME) $?

%.o: %.c
	@printf "Compiling $?\n"
	@$(CC) $(CFLAGS) -c $? -o $@

clean:
	@$(RM) $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT)

re: fclean all
