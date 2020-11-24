NAME = libft.a
CC = gcc
FLAGS = -Wall -Werror -Wextra -c

SRC =	ft_memset.c \
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
		ft_split.c\
		ft_strjoin.c\
		ft_strmapi.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_strldup.c\
		get_next_line.c\

SRC2 =	ft_lstnew.c\
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

OBJ = $(SRC:.c=.o)

OBJ2 = $(SRC2:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(FLAGS) $(SRC)
	@echo Compiling $(NAME)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@rm -f $(OBJ) $(OBJ2)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus: $(OBJ) $(OBJ2)
	@ar rc $(NAME) $(OBJ) $(OBJ2)
	@ranlib $(NAME)

.PHONY: clean fclean all re bonus
