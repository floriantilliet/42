CC = cc
CFLAGS = -Wall -Wextra -Werror -g3 
SRC_CLIENT = client.c
SRC_SERVER = server.c
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)
OBJ_SERVER = $(SRC_SERVER:.c=.o)
EXECUTABLE_CLIENT = client
EXECUTABLE_SERVER = server

all: $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER)

$(EXECUTABLE_CLIENT): $(OBJ_CLIENT)
	make -C libft bonus
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft

$(EXECUTABLE_SERVER): $(OBJ_SERVER)
	make -C libft bonus
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ_CLIENT) $(OBJ_SERVER)
	make -C libft clean

fclean: clean
	rm -f $(EXECUTABLE_CLIENT) $(EXECUTABLE_SERVER)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re