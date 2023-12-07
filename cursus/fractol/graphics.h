#ifndef GRAPHICS_H
# define GRAPHICS_H

#include <stdlib.h>
#include "mlx/mlx.h"
#include <X11/keysym.h>

typedef struct	s_data {
    void    *mlx;
    void    *win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	time_t	start;
	time_t	end;
	int	key_pressed;
}				t_data;

int	create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
int	get_opposite(int trgb);
int	add_shade(double distance, int trgb);
void    my_mlx_pixel_put(t_data *data, int x, int y, int color);

#endif