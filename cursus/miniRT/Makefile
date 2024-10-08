CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC = $(wildcard *.c)
OBJ = $(SRC:.c=.o)
EXECUTABLE = miniRT
MLX = mlx/libmlx.a

all: $(MLX) $(EXECUTABLE)

$(EXECUTABLE): $(OBJ)
	make -C libft all
	make -C get_next_line all
	$(CC) $(CFLAGS) -o $@ $^ -Llibft -lft -Lget_next_line -lgnl mlx/libmlx.a -lXext -lX11 -lm

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	make -C libft clean
	make -C get_next_line clean
	rm -rf mlx
	

fclean: clean
	rm -f $(EXECUTABLE)
	make -C libft fclean
	make -C get_next_line fclean

mlx:
	git clone https://github.com/42Paris/minilibx-linux.git $@

$(MLX): mlx
	cd mlx && make

re: fclean all

.PHONY: all clean fclean re