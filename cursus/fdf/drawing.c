/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:09:09 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/06 16:10:34 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double	interpolate_altitude(t_point start, t_point end, t_point current)
{
	double	dx;
	double	dy;
	double	dz;
	double	distance;
	double	interpolated_z;

	dx = end.x - start.x;
	dy = end.y - start.y;
	dz = end.z - start.z;
	distance = sqrt((current.x - start.x) * (current.x - start.x) + (current.y
				- start.y) * (current.y - start.y));
	interpolated_z = start.z + (distance / sqrt(dx * dx + dy * dy)) * dz;
	return (interpolated_z);
}

void	ft_draw_line(t_data *data, t_point P0, t_point P1)
{
	int		dx;
	int		sx;
	int		dy;
	int		sy;
	int		err;
	int		e2;
	t_point	start;
	t_point	end;
	t_point	current;

	start = P0;
	end = P1;
	dx = fabs(P0.x - P1.x);
	if (P0.x < P1.x)
		sx = 1;
	else
		sx = -1;
	dy = -fabs(P1.y - P0.y);
	if (P0.y < P1.y)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		current.x = P0.x;
		current.y = P0.y;
		current.z = interpolate_altitude(start, end, current);
		ft_pixel_put(&data->img, P0.x, P0.y, get_color(current.z, data->floor,
				data->ceiling));
		// ft_pixel_put(&data->img, P0.x, P0.y, 0x00FF00FF);
		if (P0.x == P1.x && P0.y == P1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			P0.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			P0.y += sy;
		}
	}
}

void	ft_draw(t_data *data, t_data proj)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{
			if (x < data->width - 1)
				ft_draw_line(data, proj.map[x][y], proj.map[x + 1][y]);
			if (y < data->height - 1)
				ft_draw_line(data, proj.map[x][y], proj.map[x][y + 1]);
			y++;
		}
		x++;
	}
}
