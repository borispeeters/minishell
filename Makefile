# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/03/11 00:50:41 by bpeeters      #+#    #+#                  #
#    Updated: 2020/07/13 09:08:22 by mpeerdem      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		minishell
HEADER =	minishell.h
INC =		includes
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
SDIR =		srcs
ODIR =		objs
_OBJS =		minishell \
			parser/parse \
			lexer/lexer lexer/lexer_status \
			utils/shell_utils
OBJS =		$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
LIBFT =		libft.a
LIBFTMAP =	libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) -L$(LIBFTMAP) -lft -o $(NAME) $(OBJS)

$(LIBFT):
	make bonus -C $(LIBFTMAP)

test: all
	./minishell

$(ODIR)/%.o: $(SDIR)/%.c $(INC)/$(HEADER)
	mkdir -p $(ODIR)/$(dir $*)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBFT)
	make clean -C $(LIBFTMAP)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTMAP)

re: fclean all
