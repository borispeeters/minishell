NAME =		minishell
HEADER =	minishell.h
INC =		includes
CC =		gcc
CFLAGS =	-Wall -Werror -Wextra
SDIR =		srcs
ODIR =		objs
_OBJS =		minishell \
			parser/parse parser/expand_env \
			lexer/lexer lexer/lexer_states lexer/verify_syntax \
			executor/execute executor/search_path executor/redirections \
			utils/shell_utils utils/array_utils utils/command_utils utils/env \
			utils/error_utils
OBJS =		$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
LIBFT =		libft.a
LIBFTMAP =	libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTMAP)/$(LIBFT)
	$(CC) -L$(LIBFTMAP) -lft -o $(NAME) $(OBJS)

$(LIBFTMAP)/$(LIBFT):
	make -C $(LIBFTMAP)

test: all
	./minishell

$(ODIR)/%.o: $(SDIR)/%.c $(INC)/$(HEADER)
	@mkdir -p $(ODIR)/$(dir $*)
	$(CC) $(CFLAGS) -I$(INC) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBFT)
	make clean -C $(LIBFTMAP)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTMAP)

re: fclean all
