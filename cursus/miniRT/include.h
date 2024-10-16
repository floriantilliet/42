/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:53:46 by florian           #+#    #+#             */
/*   Updated: 2024/10/16 09:24:00 by florian          ###   ########.fr       */
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
	float		xy;
	float		xz;
	float		yx;
	float		yz;
	float		zx;
	float		zy;
}				t_shearing_params;

typedef struct s_ray
{
	t_tuple		origin;
	t_tuple		direction;
}				t_ray;

typedef struct s_array
{ 
  float *array;
  size_t used;
  size_t size;
}			   t_array;

typedef struct s_material
{
	t_tuple		color;
	float		ambient;
	float		diffuse;
	float		specular;
	float		shininess;
}				t_material;

typedef struct s_objects
{
	int			id;
	t_tuple		origin;
	t_4matrix	transformation;
	t_array		*intersections;
	t_material	material;
	struct s_objects	*next;

}				t_objects;

typedef struct s_light
{
	t_tuple		position;
	t_tuple		intensity;
}				t_light;

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
float determinant2(t_2matrix a);
float determinant3(t_3matrix a);
float determinant4(t_4matrix a);
t_4matrix inverse4(t_4matrix a);
t_4matrix translation_mat(float x, float y, float z);
t_tuple	create_point(double x, double y, double z);
t_tuple	create_vector(double x, double y, double z);
t_4matrix rotation_x_mat(float angle);
t_4matrix rotation_y_mat(float angle);
t_4matrix rotation_z_mat(float angle);
t_4matrix scaling_mat(float x, float y, float z);
t_4matrix shearing_mat(t_shearing_params params);
t_tuple	add_floats(t_tuple a, t_tuple b);
t_tuple	substract_floats(t_tuple a, t_tuple b);
t_tuple multiply_tuple(t_tuple a, double b);
t_ray	create_ray(t_tuple origin, t_tuple direction);
t_tuple	get_position(t_ray ray, double t);
int sphere_intersections(t_ray ray, t_objects *sphere);
double	scalar_product(t_tuple a, t_tuple b);
float *init_intersections(void);
float *add_intersection(float *intersections, float t);
t_objects	**init_objects(void);
t_objects	*create_object(t_tuple origin, t_array *intersections);
void	add_object(t_objects **objects, t_objects *new_objects);
void print_intersections(float *intersections);
float hit(float *intersections);
t_ray transform_ray(t_ray ray, t_4matrix matrix);
void    add_transformation(t_objects *object, t_4matrix transformation);
t_4matrix	identity4(void);
t_tuple	normalize_vector(t_tuple a);
t_4matrix	mat_transpose(t_4matrix a);
t_tuple sphere_normal(t_objects *sphere, t_tuple world_point);
t_tuple sphere_reflect(t_tuple in, t_tuple normal);
int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
t_material create_material(t_tuple color, float ambient, float diffuse, float specular, float shininess);
t_tuple add_colors(t_tuple color1, t_tuple color2);
t_tuple substract_colors(t_tuple color1, t_tuple color2);
t_tuple multiply_color(t_tuple color, double scalar);
t_tuple color_product(t_tuple color1, t_tuple color2);
int tuple_to_trgb(t_tuple color);
t_tuple lighting(t_material material, t_light light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector);
t_light create_light(t_tuple position, t_tuple intensity);

t_array *initArray(size_t initialSize);
void insertArray(t_array *a, float element);
float hit_array(t_array *intersections);
void printArray(t_array *a);
#endif