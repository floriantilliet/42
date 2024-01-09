/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   images_and_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 14:49:00 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:41:06 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	ft_init_image(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
		return (0);
	data->win_ptr = mlx_new_window(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT,
			"fdf");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		return (0);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	if (data->img.mlx_img == NULL)
	{
		free(data->img.mlx_img);
		return (0);
	}
	data->img.addr = mlx_get_data_addr(data->img.mlx_img, &data->img.bpp,
			&data->img.line_len, &data->img.endian);
	return (1);
}

int	close_image(t_data *data)
{
	int	x;

	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	x = 0;
	while (x < data->width)
	{
		free(data->map[x]);
		x++;
	}
	free(data->map);
	exit(0);
	return (0);
}

int	render(t_data *data)
{
	t_data	proj;
	int		x;

	if (data->win_ptr == NULL)
		return (1);
	if (data->img.mlx_img)
	{
		mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	}
	data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH,
			WINDOW_HEIGHT);
	proj = ft_iso_projection(data);
	ft_draw(data, proj);
	x = 0;
	while (x < data->width)
	{
		free(proj.map[x]);
		x++;
	}
	free(proj.map);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0,
		0);
	return (0);
}

void	init_shifts(t_data *data)
{
	data->mouse_button = 0;
	data->angle_x = 0;
	data->angle_y = 0;
	data->angle_z = 0;
	data->offset_x = 0;
	data->offset_y = 0;
}

void	get_limits(t_data *data)
{
	int	i;
	int	j;

	data->floor = 0;
	data->ceiling = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j].x != -1)
		{
			if (data->map[i][j].z < data->floor)
				data->floor = data->map[i][j].z;
			if (data->map[i][j].z > data->ceiling)
				data->ceiling = data->map[i][j].z;
			j++;
		}
		i++;
	}
	data->width = i;
	data->height = j;
	data->ideal_zoom = fmin(WINDOW_WIDTH / data->width, WINDOW_HEIGHT
			/ data->height) / 2;
	data->zoom = data->ideal_zoom;
}
