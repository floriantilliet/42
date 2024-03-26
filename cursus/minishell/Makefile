CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = minishell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	make -C libft bonus
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
