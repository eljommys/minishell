NAME	=	minishell

SRCS	=	main.c\
			check.c\

OBJS	= $(SRCS:.c=.o)

LIBFT	= libft/libft.a
L_PATH	= ./libft/

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra

all: $(NAME)

$(NAME):
	make -C $(L_PATH)
	$(CC) $(SRCS) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean $(NAME)
