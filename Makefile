CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BUILTINS = $(addsuffix .c, $(addprefix srcs/builtins/, ms_cd ms_echo ms_env ms_exit ms_pwd ms_export ms_unset))
SFILES = $(addsuffix .c, $(addprefix srcs/, minishell env_array cmd_executor cmd_splitter cmd_expander cmd_redirector cmd_checker utils cmd_parser arg_splitter))
SRCS= \
	$(BUILTINS) \
	$(SFILES)
OBJS= \
	$(SRCS:.c=.o)
LIBFT= \
	./libft/libft.a
LDFLAGS= \
	-L ./libft
LFLAGS= \
	-lft \
	-lreadline
NAME= \
	minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) -o $@ $(LDFLAGS) $(LFLAGS)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

valgrind:
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=readline.supp -s ./$(NAME)

.PHONY: clean fclean re valgrind

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
