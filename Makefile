CC = cc
CFLAGS = -Wall -Wextra -Werror -g
SRCS= \
	./minishell.c \
	./minishell-lexer0.c \
	./minishell-lexer1.c
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

luke:
	cc $(BUILTINS) $(LW) $(LDFLAGS) $(LFLAGS) -o $(NAME)

$(OBJS): %.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C ./libft

.PHONY: clean fclean re

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all
