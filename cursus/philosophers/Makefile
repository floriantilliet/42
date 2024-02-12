CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = philo

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	make -C libft bonus
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean

fclean: clean
	rm -f $(EXECUTABLE)
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re