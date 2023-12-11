#ifndef GRAPHICS_H
# define GRAPHICS_H

#include <stdlib.h>
#include "mlx/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

typedef struct	s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
}	t_img;

typedef struct	s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img	img;
}	t_data;

typedef struct	s_point
{
    int	x;
    int	y;
    int	z;
}	t_point;


int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	ft_get_t(int trgb);
unsigned char	ft_get_r(int trgb);
unsigned char	ft_get_g(int trgb);
unsigned char	ft_get_b(int trgb);
int	ft_get_opposite(int trgb);
int	ft_add_shade(double distance, int trgb);
void    ft_pixel_put(t_img *img, int x, int y, int color);
void	ft_draw_line(t_data *data, t_point P0, t_point P1, int color);
void	ft_iso_projection(int *x, int *y, int z);

#endif