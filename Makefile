NAME =	minishell

SRCS =	srcs/main.c\
		srcs/parser.c\
		srcs/pipe.c\
		srcs/command.c\
		srcs/args.c\
		srcs/bin.c\
		srcs/builtins.c\
		srcs/bash.c\
		srcs/cd.c\
		srcs/export.c\
		srcs/unset.c\
		srcs/utils.c\
		srcs/lens.c\
		srcs/exit.c\
		srcs/stty.c\
		srcs/cmd_handler.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra -g3 -fsanitize=address

all:		$(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c -I./libft/ $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
		cd ./libft/ && make
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS) ./libft/libft.a

clean:
		$(RM) $(OBJS)
		@make clean -C libft

fclean:		clean
		$(RM) $(NAME)
		@make fclean -C libft

re:		fclean all

leaks:
	valgrind --leak-check=full --show-leak-kinds=all ./$(NAME)

git:
	make fclean
	git add .
	git commit -m "make done"
	git push

norme:
	norminette ./srcs/* ./libft/*

.PHONY:		all clean fclean re leaks git norme
