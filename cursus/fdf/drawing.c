/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 16:09:09 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/09 15:49:21 by florian          ###   ########.fr       */
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

void	update_err(t_bresenham *bres, t_point *P0)
{
	int	e2;

	e2 = 2 * bres->err;
	if (e2 >= bres->dy)
	{
		bres->err += bres->dy;
		P0->x += bres->sx;
	}
	if (e2 <= bres->dx)
	{
		bres->err += bres->dx;
		P0->y += bres->sy;
	}
}

void	draw_line_loop(t_data *data, t_point *P0, t_point P1, t_bresenham *bres)
{
	t_point	current;

	while (1)
	{
		current.x = P0->x;
		current.y = P0->y;
		current.z = interpolate_altitude(bres->start, bres->end, current);
		ft_pixel_put(&data->img, P0->x, P0->y, get_color(current.z, data->floor,
				data->ceiling));
		if (P0->x == P1.x && P0->y == P1.y)
			break ;
		update_err(bres, P0);
	}
}

void	ft_draw_line(t_data *data, t_point P0, t_point P1)
{
	t_bresenham	bres;

	bres.dx = fabs(P0.x - P1.x);
	if (P0.x < P1.x)
		bres.sx = 1;
	else
		bres.sx = -1;
	bres.dy = -fabs(P1.y - P0.y);
	if (P0.y < P1.y)
		bres.sy = 1;
	else
		bres.sy = -1;
	bres.err = bres.dx + bres.dy;
	bres.start = P0;
	bres.end = P1;
	draw_line_loop(data, &P0, P1, &bres);
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
