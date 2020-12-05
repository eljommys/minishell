NAME =	minishell

SRCS =	srcs/main.c\
		srcs/builtins.c\
		srcs/bash.c\
		srcs/env.c\
		srcs/bin.c\
		srcs/utils.c\
		srcs/parser.c\
		srcs/command.c\
		srcs/args.c\
		srcs/lens.c\
		srcs/pipe.c\
		srcs/cd.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

RM = rm -rf

CFLAGS = -Wall -Werror -Wextra -g3

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
	norminette ./srcs/*

.PHONY:		all clean fclean re leaks git norme
