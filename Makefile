# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/11 00:50:41 by bpeeters      #+#    #+#                  #
#    Updated: 2020/06/30 15:45:08 by bpeeters      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
HEADER =	minishell.h
INC =		includes
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
SDIR =		srcs
ODIR =		objs
_OBJS =		main
OBJS =		$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
LIBFT =		libft.a
LIBFTMAP =	libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -L. -lft -o $(NAME) $(OBJS)

$(LIBFT):
	make -C $(LIBFTMAP)
	cp $(LIBFTMAP)/$(LIBFT) .

test: all
	@./minishell

$(ODIR)/%.o: $(SDIR)/%.c $(INC)/$(HEADER)
	@mkdir -p $(ODIR)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	@$(RM) $(OBJ)
	@$(RM) libftprintf.a
	@make clean -C $(LIBFTMAP)

fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFTMAP)

re: fclean all
