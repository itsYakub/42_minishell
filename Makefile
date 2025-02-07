CC = cc
CFLAGS = -Wall -Wextra -Werror -g
BUILTINS = $(addsuffix .c, $(addprefix ./builtins/, ms_cd ms_echo ms_env ms_exit ms_pwd ms_export ms_unset))
LW = $(addsuffix .c, $(addprefix ./lw/, lw env_array vl_env))
SRCS= \
	./minishell.c \
	./minishell-getenv.c \
	./minishell-utilpath.c \
	./lw/env_array.c \
	./lw/main_bonus.c \
	./lw/utils_bonus.c
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

