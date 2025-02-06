CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BUILTINS = $(addprefix ./builtins/, ms_cd.c ms_echo.c ms_env.c ms_exit.c ms_pwd.c)
SRCS= \
	./minishell.c $(BUILTINS) lw.c vl_env.c
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

.PHONY: clean fclean re

clean:
	make -C ./libft clean
	rm -f $(OBJS)

fclean: clean
	make -C ./libft fclean
	rm -f $(NAME)

re: fclean all

