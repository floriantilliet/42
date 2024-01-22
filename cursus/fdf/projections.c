/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projections.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 12:57:01 by florian           #+#    #+#             */
/*   Updated: 2024/01/22 17:57:46 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

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

	if (data->projection == 1)
	{
		rots.rot_z = ft_get_rot_matrix(45 + data->angle_z, 'z');
		rots.rot_x = ft_get_rot_matrix(atan(sqrt(2)) + 45 + data->angle_x, 'x');
		rots.rot_y = ft_get_rot_matrix(-data->angle_y, 'y');
	}
	if (data->projection == 0)
	{
		rots.rot_z = ft_get_rot_matrix(90 + data->angle_z, 'z');
		rots.rot_x = ft_get_rot_matrix(0 + data->angle_x, 'x');
		rots.rot_y = ft_get_rot_matrix(0 + data->angle_y, 'y');
	}
	ft_allocate_proj_map(&proj, data->width, data->height);
	ft_apply_transformations(&proj, data, &rots);
	return (proj);
}
