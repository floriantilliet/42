/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hooks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:50:34 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/09 15:49:27 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	ft_mouse_down(int button, int x, int y, t_data *data)
{
	if (button == 4)
		data->zoom += 0.05 * data->zoom;
	if (button == 5)
		data->zoom -= 0.05 * data->zoom;
	if (button == 1)
	{
		data->prev_x = x;
		data->prev_y = y;
		data->mouse_button = 1;
	}
	if (button == 3)
	{
		data->prev_x = x;
		data->prev_y = y;
		data->mouse_button = 3;
	}
	return (0);
}

int	ft_mouse_up(int button, int x, int y, t_data *data)
{
	if (button == 1 || button == 3)
	{
		data->mouse_button = 0;
		x++;
		y++;
	}
	return (0);
}

int	ft_mouse_move(int x, int y, t_data *data)
{
	if (data->mouse_button == 1)
	{
		data->offset_x += (x - data->prev_x) / data->zoom;
		data->offset_y += (y - data->prev_y) / data->zoom;
		data->prev_x = x;
		data->prev_y = y;
	}
	if (data->mouse_button == 3)
	{
		data->angle_x -= (y - data->prev_y) * 0.1;
		data->angle_y -= (x - data->prev_x) * 0.1;
		data->prev_x = x;
		data->prev_y = y;
	}
	return (0);
}
