/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:30:48 by florian           #+#    #+#             */
/*   Updated: 2024/01/31 11:08:14 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "get_next_line/get_next_line_bonus.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# define MLX_ERROR 1

# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024
# define DEG_TO_RAD 3.14159265358979323846 / 180.0

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_point		**map;

	int			projection;

	double		angle_x;
	double		angle_y;
	double		angle_z;

	double		offset_x;
	double		offset_y;

	double		zoom;

	int			mouse_button;
	double		prev_x;
	double		prev_y;

	double		ceiling;
	double		floor;
	double		height;
	double		width;
	double		ideal_zoom;
}				t_data;

typedef struct s_matrix
{
	t_point		i;
	t_point		j;
	t_point		k;
}				t_matrix;

typedef struct s_bresenham
{
	int			dx;
	int			sx;
	int			dy;
	int			sy;
	int			err;
	t_point		start;
	t_point		end;
}				t_bresenham;

typedef struct s_rot_matrices
{
	t_matrix	rot_z;
	t_matrix	rot_x;
	t_matrix	rot_y;
}				t_rot_matrices;

int				ft_create_trgb(unsigned char t, unsigned char r,
					unsigned char g, unsigned char b);
void			ft_pixel_put(t_img *img, unsigned int x, unsigned int y,
					int color);
void			ft_draw_line(t_data *data, t_point P0, t_point P1);
t_data			ft_iso_projection(t_data *data);
t_matrix		ft_get_rot_matrix(double deg, char axis);
t_point			ft_multiply_vector_by_matrix(t_point *v, t_matrix m);
double			interpolate_altitude(t_point start, t_point end,
					t_point current);
char			**fd_to_tab(int fd);
char			***tab_to_tabs(char **tab);
t_point			**tabs_to_map(char ***tabs);
void			ft_draw(t_data *data, t_data proj);
void			get_limits(t_data *data);
int				get_color(double z, double min_altitude, double max_altitude);
int				key_hook(int keycode, t_data *data);
int				arrow_move_hook(int keycode, t_data *data);
int				key_rotation_hook(int keycode, t_data *data);
int				key_reset_and_close_hook(int keycode, t_data *data);
int				close_image(t_data *data);
int				ft_mouse_down(int button, int x, int y, t_data *data);
int				ft_mouse_up(int button, int x, int y, t_data *data);
int				ft_mouse_move(int x, int y, t_data *data);
void			ft_project_point(t_point *point, t_matrix rot_z, t_matrix rot_x,
					t_matrix rot_y);
void			ft_offset_and_zoom(t_point *point, t_data *data, int x, int y);
double			interpolate_altitude(t_point start, t_point end,
					t_point current);
void			update_err(t_bresenham *bres, t_point *P0);
void			draw_line_loop(t_data *data, t_point *P0, t_point P1,
					t_bresenham *bres);
void			ft_allocate_proj_map(t_data *proj, int width, int height);
t_point			ft_apply_single_transformation(t_point point,
					t_rot_matrices *rots, t_data *data);
void			ft_apply_transformations(t_data *proj, t_data *data,
					t_rot_matrices *rots);
char			*read_file_into_str(int fd);
void			free_map(t_point **map);
void			free_tabs(char ***tabs);
void			free_tab(char **tab);
t_point			*allocate_and_init_line(char **tab_line, int i);
t_point			create_point_from_tab(char **tab, int i, int j);
int				render(t_data *data);
int				ft_get_map(t_data *data, char *path);
int				ft_init_image(t_data *data);
void			init_shifts(t_data *data);
void			ft_loop_hooks(t_data *data);

#endif