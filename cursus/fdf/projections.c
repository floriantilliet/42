/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:57:01 by florian           #+#    #+#             */
/*   Updated: 2024/01/08 17:18:33 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double	rad(double deg)
{
	return (deg * DEG_TO_RAD);
}

t_point	ft_multiply_vector_by_matrix(t_point *v, t_matrix m)
{
	t_point	res;

	res.x = v->x * m.i.x + v->y * m.i.y + v->z * m.i.z;
	res.y = v->x * m.j.x + v->y * m.j.y + v->z * m.j.z;
	res.z = v->x * m.k.x + v->y * m.k.y + v->z * m.k.z;
	return (res);
}

t_matrix	ft_get_rot_matrix(double deg, char axis)
{
	if (axis == 'x')
		return ((t_matrix){(t_point){1., 0., 0.}, (t_point){0., cos(rad(deg)),
			-sin(rad(deg))}, (t_point){0., sin(rad(deg)), cos(rad(deg))}});
	if (axis == 'y')
		return ((t_matrix){(t_point){cos(rad(deg)), 0., -sin(rad(deg))},
			(t_point){0., 1., 0.}, (t_point){sin(deg), 0., cos(rad(deg))}});
	if (axis == 'z')
		return ((t_matrix){(t_point){cos(rad(deg)), -sin(rad(deg)), 0.},
			(t_point){sin(rad(deg)), cos(rad(deg)), 0.}, (t_point){0., 0.,
			1.}});
	return ((t_matrix){
		(t_point){1., 0., 0.},
		(t_point){0., 1., 0.},
		(t_point){0., 0., 1.},
	});
}

void	ft_allocate_proj_map(t_data *proj, int width, int height)
{
	int	x;

	x = 0;
	proj->map = malloc(sizeof(t_point *) * width);
	while (x < width)
	{
		proj->map[x] = malloc(sizeof(t_point) * height);
		x++;
	}
}

t_point	ft_apply_single_transformation(t_point point, t_rot_matrices *rots,
		t_data *data)
{
	point = ft_multiply_vector_by_matrix(&point, rots->rot_z);
	point = ft_multiply_vector_by_matrix(&point, rots->rot_x);
	point = ft_multiply_vector_by_matrix(&point, rots->rot_y);
	point.x *= -1;
	point.y += data->offset_y;
	point.x += data->offset_x;
	point.x = round(point.x * data->zoom);
	point.y = round(point.y * data->zoom);
	point.x += WINDOW_WIDTH / 2;
	point.y += WINDOW_HEIGHT / 2;
	return (point);
}

void	ft_apply_transformations(t_data *proj, t_data *data,
		t_rot_matrices *rots)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			proj->map[x][y] = ft_apply_single_transformation(data->map[x][y],
					rots, data);
			proj->map[x][y].z = data->map[x][y].z;
			y++;
		}
		x++;
	}
}

t_data	ft_iso_projection(t_data *data)
{
	t_data			proj;
	t_rot_matrices	rots;

	rots.rot_z = ft_get_rot_matrix(45 + data->angle_z, 'z');
	rots.rot_x = ft_get_rot_matrix(atan(sqrt(2)) + 45 + data->angle_x, 'x');
	rots.rot_y = ft_get_rot_matrix(-data->angle_y, 'y');
	ft_allocate_proj_map(&proj, data->width, data->height);
	ft_apply_transformations(&proj, data, &rots);
	return (proj);
}
