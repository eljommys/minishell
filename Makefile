NAME	=	minishell

SRCS	=	main.c\
			builtins.c\
			bash.c\
			env.c\
			bin.c\
			utils.c\
			parser.c\
			command.c\
			args.c\
			lens.c\

OBJS	=	$(SRCS:.c=.o)

LIBFT	= libft/libft.a
L_PATH	= ./libft/

CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g3

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

git:
	make ffclean
	git add .
	git commit -m "make done"
	git push

.PHONY: all clean fclean ffclean re
