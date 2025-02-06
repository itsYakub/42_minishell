CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS= \
	./minishell.c
OBJS= \
	$(SRCS:.c=.o)
LIBFT= \
	./libft/libft.a
LDFLAGS= \
	-L ./libft
LFLAGS= \
	-lft
NAME= \
	minishell

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(LFLAGS)

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

