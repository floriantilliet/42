/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:53:46 by florian           #+#    #+#             */
/*   Updated: 2024/11/13 11:33:10 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

#include <stdio.h>

# include "get_next_line/get_next_line_bonus.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# define EPSILON 0.00001
# define WINDOW_WIDTH 800
# define WINDOW_HEIGHT 800
# define DEG_TO_RAD 3.14159265358979323846 / 180.0
# define PI 3.14159265358979323846

typedef struct s_tuple
{
	double		x;
    double		y;
    double		z;
    double		w;
}				t_tuple;

typedef struct		s_4matrix{
	double			mat[4][4];
}					t_4matrix;

typedef struct		s_3matrix{
	double			mat[3][3];
}					t_3matrix;

typedef struct		s_2matrix{
	double			mat[2][2];
}					t_2matrix;

typedef struct s_shearing_params
{
	double		xy;
	double		xz;
	double		yx;
	double		yz;
	double		zx;
	double		zy;
}				t_shearing_params;

typedef struct s_ray
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;

typedef struct s_material
{
	t_tuple		color;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
}				t_material;

typedef struct s_objects
{
	int			id;
	t_4matrix	transformation;
	t_material	material;
	struct s_objects	*next;

}				t_objects;

typedef struct s_intersection
{
	double		t;
	t_objects	*object;
}				t_intersection;

typedef struct s_array
{ 
  t_intersection *array;
  size_t used;
  size_t size;
}			   t_array;

typedef struct s_light
{
	t_tuple		position;
	t_tuple		intensity;
}				t_light;

typedef struct s_computations
{
	double t;
	t_objects *object;
	t_tuple point;
	t_tuple eyev;
	t_tuple normalv;
	int inside;
}			t_computations;

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double	field_of_view;
	t_4matrix	transform;
	double	half_width;
	double	half_height;
	double	pixel_size;
}			t_camera;

typedef struct s_world
{
	t_objects **objects;
	t_light		light;
	
}			t_world;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_data;

int	ft_init_image(t_data *data);
int	close_image(t_data *data);
int mat_equal(t_4matrix a, t_4matrix b);
t_4matrix mat_product(t_4matrix a, t_4matrix b);
t_tuple mat_tuple_product(t_4matrix a, t_tuple b);
t_3matrix sub4matrix(t_4matrix a, int row, int col);
t_2matrix sub3matrix(t_3matrix a, int row, int col);
double determinant2(t_2matrix a);
double determinant3(t_3matrix a);
double determinant4(t_4matrix a);
t_4matrix inverse4(t_4matrix a);
t_4matrix translation_mat(double x, double y, double z);
t_tuple	create_point(double x, double y, double z);
t_tuple	create_vector(double x, double y, double z);
t_4matrix rotation_x_mat(double angle);
t_4matrix rotation_y_mat(double angle);
t_4matrix rotation_z_mat(double angle);
t_4matrix scaling_mat(double x, double y, double z);
t_4matrix shearing_mat(t_shearing_params params);
t_tuple	add_doubles(t_tuple a, t_tuple b);
t_tuple	substract_doubles(t_tuple a, t_tuple b);
t_tuple multiply_tuple(t_tuple a, double b);
t_ray	create_ray(t_tuple origin, t_tuple direction);
t_tuple	get_position(t_ray ray, double t);
t_array *sphere_intersections(t_ray ray, t_objects *sphere);
double	scalar_product(t_tuple a, t_tuple b);
t_tuple	cross_product(t_tuple a, t_tuple b);
t_objects	**init_objects(void);
t_objects	*create_object(t_4matrix transformation, t_material material);
void	add_object(t_objects **objects, t_objects *new_objects);
t_ray transform_ray(t_ray ray, t_4matrix matrix);
void    add_transformation(t_objects *object, t_4matrix transformation);
t_4matrix	identity4(void);
t_tuple	normalize_vector(t_tuple a);
t_4matrix	mat_transpose(t_4matrix a);
t_tuple sphere_normal(t_objects *sphere, t_tuple world_point);
t_tuple sphere_reflect(t_tuple in, t_tuple normal);
int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
t_material create_material(t_tuple color, double ambient, double diffuse, double specular, double shininess);
t_tuple add_colors(t_tuple color1, t_tuple color2);
t_tuple substract_colors(t_tuple color1, t_tuple color2);
t_tuple multiply_color(t_tuple color, double scalar);
t_tuple color_product(t_tuple color1, t_tuple color2);
int tuple_to_trgb(t_tuple color);
t_tuple lighting(t_material material, t_light light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector);
t_light create_light(t_tuple position, t_tuple intensity);
t_array *intersect_world(t_ray ray, t_world *world);
t_world *init_world(void);
t_computations prepare_computations(t_intersection intersection, t_ray ray);
t_camera create_camera(double hsize, double vsize, double field_of_view);
void	ft_pixel_put(t_img *img, unsigned int x, unsigned int y, int color);
void render(t_world *world, t_camera camera, t_data data);
t_4matrix view_transform(t_tuple from, t_tuple to, t_tuple up);
int hit_index(t_array *a, double t);
double	get_magnitude(t_tuple a);

t_array *init_array(size_t initialSize);
void insert_array(t_array *a, double element, t_objects *object);
void print_array(t_array *a);
t_intersection hit_array(t_array *a);
t_array *concatenate_array(t_array *a, t_array *b);
void sort_array(t_array *a);

#endif