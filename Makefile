# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: bpeeters <bpeeters@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2020/09/16 14:16:44 by bpeeters      #+#    #+#                  #
#    Updated: 2020/09/17 10:33:06 by bpeeters      ########   odam.nl          #
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
			lexer/lexer lexer/lexer_special lexer/lexer_states \
			lexer/verify_syntax \
			parser/escape_quotes parser/expand_env parser/parse \
			parser/parser_redirect parser/quote_removal \
			parser/quote_removal_states parser/replace_env \
			parser/split_words parser/word_split_realloc \
			executor/exec_loop executor/execute executor/pipes \
			executor/redirections executor/search_path executor/wait \
			utils/array_utils utils/command_utils utils/error_utils \
			utils/expansion_utils utils/parse_utils utils/prompt \
			utils/shell_utils utils/signal utils/valid_key \
			env/env_error_utils env/env_split env/get_set_env env/init_env \
			env/resize_env \
			builtins/builtin_cd builtins/builtin_echo builtins/builtin_env \
			builtins/builtin_exit builtins/builtin_export \
			builtins/builtin_pwd builtins/builtin_unset
OBJS =		$(addsuffix .o, $(addprefix $(ODIR)/, $(_OBJS)))
LIBFT =		libft.a
LIBFTMAP =	libft

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJS) $(LIBFTMAP)/$(LIBFT)
	$(CC) -L$(LIBFTMAP) -lft -o $(NAME) $(OBJS)

$(LIBFTMAP)/$(LIBFT):
	make -C $(LIBFTMAP)

$(ODIR)/%.o: $(SDIR)/%.c $(INC)/$(HEADER)
	@mkdir -p $(ODIR)/$(dir $*)
	$(CC) $(CFLAGS) -I$(INC) -I$(LIBFTMAP) -c $< -o $@

clean:
	$(RM) $(OBJS)
	$(RM) $(LIBFT)
	make clean -C $(LIBFTMAP)

fclean: clean
	$(RM) $(NAME)
	make fclean -C $(LIBFTMAP)

re: fclean all
