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

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS += -Wall -Werror -Wextra -g3 -fsanitize=address

RM = rm -rf

LIBFT = libft.a
LIBFTDIR = libft/
LIBFTLINK = -L $(LIBFTDIR) -lft


all:		$(NAME)

$(NAME):	complib echoCL $(OBJS) echoOK echoCS
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LIBFTLINK)

complib:
	$(MAKE) -C libft/

%.o:		%.c
	$(CC) -c $(CFLAGS) -o $@ $<
	printf "$(GREEN)██"

clean: echoCLEAN
	$(MAKE) -C $(LIBFTDIR) clean
	$(RM) $(OBJS)

fclean: clean echoFCLEAN
	$(MAKE) -C $(LIBFTDIR) fclean
	$(RM) $(OBJS)
	$(RM) $(NAME)

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
.SILENT:

##############______________Colors______________##############

BLACK = \033[1;30m
RED = \033[1;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[1;34m
PURPLE = \033[1;35m
CYAN = \033[1;36m
WHITE = \033[1;37m
END = \033[0m

##############______________MESSAGES______________##############

echoCL:
	echo "$(YELLOW)===> Compiling $(RED)Minishell$(END)\n"
echoOK:
	echo "$(GREEN) OK$(END)\n"
echoCS :
	echo "$(GREEN)===> Compilation Success$(END)\n"
echoCLEAN :
	echo "\n$(PURPLE)===> Cleanning OBJS$(END)"
echoFCLEAN :
	echo "$(PURPLE)===> Cleanning Exec & Lib$(END)\n"
