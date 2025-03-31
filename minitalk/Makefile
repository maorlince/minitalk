NAME = minitalk

SRV_SRC = 	server.c \
			ft_printf.c \
			ft_printf_utils.c \
			libft.c
CLT_SRC = 	client.c \
			ft_printf.c \
			ft_printf_utils.c \
			libft.c

SRV_OBJ := $(SRV_SRC:%.c=%.o)
CLT_OBJ := $(CLT_SRC:%.c=%.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): client server

client: $(CLT_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

server: $(SRV_OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -Iincludes -c $< -o $@

clean:
	rm -f $(SRV_OBJ) $(CLT_OBJ)
	rm -f client server

re: fclean all

.PHONY: all clean fclean re