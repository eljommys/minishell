NAME 		= 	libft.a
OBJS		=	${SRCS:.c=.o}
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror

SRCS =	ft_memset.c \
		ft_bzero.c \
		ft_memcpy.c \
		ft_memccpy.c \
		ft_memmove.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_strlen.c \
		ft_strlcpy.c\
		ft_strlcat.c \
		ft_strchr.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncpy.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_isalnum.c \
		ft_isascii.c \
		ft_isprint.c \
		ft_toupper.c \
		ft_tolower.c \
		ft_calloc.c \
		ft_strdup.c\
		ft_itoa.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_putstrlen_fd.c\
		ft_putstrs_fd.c\
		ft_split.c\
		ft_split_case.c\
		ft_strjoin.c\
		ft_strmapi.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_strldup.c\
		get_next_line.c\
		ft_lstnew.c\
		ft_lstadd_front.c\
		ft_lstnew.c\
		ft_lstsize.c\
		ft_lstlast.c\
		ft_lstlast.c\
		ft_lstadd_back.c\
		ft_lstdelone.c\
		ft_lstclear.c\
		ft_lstiter.c\
		ft_lstmap.c\

###########################

OPTI = -Ofast #-O3

all:		$(NAME)

$(NAME):	echoCL ${OBJS} echoOK echoCS echoAR
	ar rc	$(NAME) ${OBJS}
	ranlib	$(NAME)

.c.o:
	${CC} -c ${CFLAGS} -I. -o $@ $<
	printf "$(GREEN)█"

clean:
	rm -f $(OBJS)

fclean:		clean
	rm -f $(NAME)

re:			fclean all

.SILENT:
###########################COLOR
#----------------reset----------------#
NC = \033[0m

#-----------Regular Colors------------#
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[32m
YELLOW = \033[33;33m
BLUE = \033[0;34m
PURPLE = \033[35m
CYAN = \033[1;36m
WHITE = \033[0;37m

###########################ECHO

echoCL:
	echo "$(YELLOW)===> Compiling Libft$(NC)\n"
echoOK:
	echo "$(GREEN) OK$(NC)\n"
echoCS :
	echo "$(GREEN)===> Compilation Success$(NC)"
echoAR :
	echo "$(CYAN)===> Archiving Libft$(NC)$(GREEN) OK$(NC)\n"