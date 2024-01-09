/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 15:39:40 by ftilliet          #+#    #+#             */
/*   Updated: 2024/01/09 15:50:26 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	key_hook(int keycode, t_data *data)
{
	arrow_move_hook(keycode, data);
	key_rotation_hook(keycode, data);
	key_reset_and_close_hook(keycode, data);
	return (0);
}

int	arrow_move_hook(int keycode, t_data *data)
{
	if (keycode == XK_Page_Up)
		data->zoom += 0.05 * data->zoom;
	if (keycode == XK_Page_Down)
		data->zoom -= 0.05 * data->zoom;
	if (keycode == XK_Up)
		data->offset_y -= 5 / data->zoom;
	if (keycode == XK_Down)
		data->offset_y += 5 / data->zoom;
	if (keycode == XK_Left)
		data->offset_x -= 5 / data->zoom;
	if (keycode == XK_Right)
		data->offset_x += 5 / data->zoom;
	return (0);
}

int	key_rotation_hook(int keycode, t_data *data)
{
	if (keycode == XK_d)
		data->angle_y -= 1;
	if (keycode == XK_a)
		data->angle_y += 1;
	if (keycode == XK_w)
		data->angle_x += 1;
	if (keycode == XK_s)
		data->angle_x -= 1;
	if (keycode == XK_e)
		data->angle_z += 1;
	if (keycode == XK_q)
		data->angle_z -= 1;
	return (0);
}

int	key_reset_and_close_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_image(data);
	if (keycode == XK_space)
	{
		data->angle_x = 0;
		data->angle_y = 0;
		data->angle_z = 0;
		data->offset_x = 0;
		data->offset_y = 0;
		data->zoom = data->ideal_zoom;
	}
	return (0);
}

void	ft_loop_hooks(t_data *data)
{
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &key_hook, data);
	mlx_hook(data->win_ptr, 17, 0L, close_image, data);
	mlx_hook(data->win_ptr, 4, 1L << 2, ft_mouse_down, data);
	mlx_hook(data->win_ptr, 5, 1L << 3, ft_mouse_up, data);
	mlx_hook(data->win_ptr, 6, 1L << 6, ft_mouse_move, data);
	mlx_loop_hook(data->mlx_ptr, &render, data);
	mlx_loop(data->mlx_ptr);
}
