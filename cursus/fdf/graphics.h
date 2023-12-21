#ifndef GRAPHICS_H
# define GRAPHICS_H

#include <stdlib.h>
#include "mlx/mlx.h"
#include <X11/keysym.h>
#include <X11/X.h>
#include <math.h>
#include <stdio.h>

#include "stdio.h"
#include "libft/libft.h"
#include "get_next_line/get_next_line_bonus.h"
#include <fcntl.h>

#define MLX_ERROR 1

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 1024
#define NB_POINTS 9

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
    t_point **map;

    double  angle_x;
    double  angle_y;
    double  angle_z;

    double  offset_x;
    double  offset_y;

    double  zoom;

    int     mouse_button;
    double  prev_x;
    double  prev_y;

    double ceiling;
    double floor;
    double height;
    double width;
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
void	ft_draw_line(t_data *data, t_point P0, t_point P1);
t_data ft_iso_projection(t_data *data);
t_matrix	ft_get_rot_matrix(double deg, char axis);
t_point ft_multiply_vector_by_matrix(t_point *v, t_matrix m);
void ft_draw_image(t_data *data, t_data proj);
void draw_lines_recursive(t_data *data,t_data proj, int start, int end, int color);
void	ft_pixel_grad(t_img *img, unsigned int x, unsigned int y, unsigned int z, int color);
int get_altitude_color(double z);
double interpolate_altitude(t_point start, t_point end, t_point current);
char** fd_to_tab(int fd);
char*** tab_to_tabs(char **tab);
t_point **tabs_to_map(char ***tabs);
void	ft_draw(t_data *data, t_data proj);
void get_limits(t_data *data);

#endif