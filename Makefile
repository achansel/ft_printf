SRCS = 	ft_printf.c \
	conversion.c \
	conversion_helper.c \
	flag_helper.c \
	serialize.c \
	utils.c

NAME  = libftprintf.a

CC    = clang
CFLAGS = -Wall -Wextra -Werror

OBJS  = $(SRCS:.c=.o)

all: $(NAME)

bonus: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	ar crs $(NAME) $(OBJS)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: bonus all clean fclean re
