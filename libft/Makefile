NAME = 	libft.a

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
		ft_isspace.c \
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
		ft_addchr.c\
		ft_skip_spaces.c\
		ft_free_matrix.c\
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

OBJS =		${SRCS:.c=.o}

CC =		gcc

CFLAGS =	-Wall -Wextra -Werror

RM = 		rm -rf

all:		$(NAME)

$(NAME):	echoCL ${OBJS} echoOK
			ar rc	$(NAME) ${OBJS}
			ranlib	$(NAME)

.c.o:
			${CC} -c ${CFLAGS} -I. -o $@ $<
			printf "$(GREEN)█"

clean:
			${RM} $(OBJS)

fclean:		clean
			${RM} $(NAME)

re:			fclean all

.SILENT:

##############______________Colors______________##############

BLUE = \033[1;34m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
END = \033[0m

##############______________MESSAGES______________##############

echoCL:
	echo "\n$(YELLOW)===> Compiling $(BLUE)Libft$(END)\n"
echoOK:
	echo "$(GREEN) OK ===> Compilation Success$(END)\n"
