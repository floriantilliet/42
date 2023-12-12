#ifndef GRAPHICS_H
# define GRAPHICS_H

#include <stdlib.h>
#include "mlx/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

typedef struct	s_img
{
    void	*mlx_img;
    char	*addr;
    int		bpp;
    int		line_len;
    int		endian;
}	t_img;

typedef struct	s_point
{
    double	x;
    double	y;
    double	z;
}	t_point;

typedef struct	s_data
{
    void	*mlx_ptr;
    void	*win_ptr;
    t_img	img;
    t_point points[9];
}	t_data;

typedef struct s_matrix
{
	t_point	i;
	t_point	j;
	t_point	k;
}	t_matrix;


int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	ft_get_t(int trgb);
unsigned char	ft_get_r(int trgb);
unsigned char	ft_get_g(int trgb);
unsigned char	ft_get_b(int trgb);
int	ft_get_opposite(int trgb);
int	ft_add_shade(double distance, int trgb);
void    ft_pixel_put(t_img *img, unsigned int x,  unsigned int y, int color);
void	ft_draw_line(t_data *data, t_point P0, t_point P1, int color);
void	ft_iso_projection(t_point *point);
t_matrix	ft_get_rot_matrix(double deg, char axis);
void ft_multiply_vector_by_matrix(t_point *v, t_matrix m);

#endif