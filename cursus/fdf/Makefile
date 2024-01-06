CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -pg
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = fdf

all: $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	make -C libft all
	make -C get_next_line all
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -Lget_next_line -lgnl libmlx.a -lXext -lX11 -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C get_next_line clean

fclean: clean
	rm -f $(EXECUTABLE)
	make -C libft fclean
	make -C get_next_line fclean

re: fclean all

.PHONY: all clean fclean re