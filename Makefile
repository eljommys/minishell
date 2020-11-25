NAME	=	minishell

SRCS	=	main.c\
			commands.c\
			bash.c\
			echo.c\
			env.c\
			bin.c\
			utils.c\

OBJS	=	$(SRCS:.c=.o)

LIBFT	= libft/libft.a
L_PATH	= ./libft/

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g

all: $(NAME)

$(NAME):
	make -C $(L_PATH)
	$(CC) -c $(SRCS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

ffclean: fclean
	make -C $(L_PATH) fclean

re: fclean $(NAME)

leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

.PHONY: all clean fclean ffclean re
