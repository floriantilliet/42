CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c) $(wildcard lexing/*.c) 
OBJ = $(SRC:.c=.o)
EXECUTABLE = minishell

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	make -C libft bonus
	$(CC) $(CFLAGS) -o $@ $^ -lreadline -Llibft -lft

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C libft clean
	rm -f $(OBJ)

fclean: clean
	make -C libft fclean
	rm -f $(EXECUTABLE)

re: fclean all

.PHONY: all clean fclean re
