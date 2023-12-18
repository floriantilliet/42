/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:20:50 by florian           #+#    #+#             */
/*   Updated: 2023/12/18 19:32:32 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "graphics.h"

int close(t_data *img)
{
    mlx_destroy_window(img->mlx_ptr, img->win_ptr);
    exit(1);
    return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		close(data);
		data->win_ptr = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	render(t_data *data)
{   
    t_data  proj;

	if (data->win_ptr == NULL)
		return (1);

    proj = ft_iso_projection(data);

    ft_draw_image(data, proj);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	key_hook(int keycode, t_data *data)
{

	if (keycode == XK_Page_Up) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
		data->zoom += 0.01;
	}

	if (keycode == XK_Page_Down) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
		data->zoom -= 0.01;
	}

	if (keycode == XK_Up) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
			data->offset_y -= 5;
	}
	
	else if (keycode == XK_Down) // Remplace KEY_DOWN par la valeur correspondant à la touche souhaitée
	{
			data->offset_y += 5;
	}

	if (keycode == XK_Left) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
			data->offset_x -= 5;
	}

	if (keycode == XK_Right)
	{
			data->offset_x += 5;
	}

	if (keycode == XK_d)
	{
        	data->angle_y -= 0.01;
	}

	if (keycode == XK_a)
	{
			data->angle_y += 0.01;
	}

    if (keycode == XK_w)
    {
        	data->angle_x += 0.01;
    }

    if (keycode == XK_s)
    {
        	data->angle_x -= 0.01;
    }

	if (keycode == XK_e)
    {
        	data->angle_z -= 1;
    }

	if (keycode == XK_q)
	{
			data->angle_z += 1;
	}

	if (keycode == XK_space)
	{
			data->angle_x = 0;
			data->angle_y = 0;
			data->angle_z = 0;
			data->offset_x = 0;
			data->offset_y = 0;
			data->zoom = 1;
	}

	if (data->img.mlx_img) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); // Libère l'image précédente
    }
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}


int	ft_mouse_down(int button, int x, int y, t_data *data)
{	
	if (button == 4)
		data->zoom += 0.01;
	
	if (button == 5)
		data->zoom -= 0.01;

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
	if (data->img.mlx_img) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); // Libère l'image précédente
    }
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
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
	//print mouse button
	printf("mouse button: %d\n", data->mouse_button);
	if (data->mouse_button == 1)
	{
		// Update offsets based on mouse movement
        data->offset_x += x - data->prev_x;
        data->offset_y += y - data->prev_y;

        // Store the current mouse position for the next movement event
        data->prev_x = x;
        data->prev_y = y;
	}

	if (data->mouse_button == 3) // Right mouse button
    {	
        // Update rotation angle based on mouse movement
        data->angle_x -= (y - data->prev_y) * 0.01; // Adjust the multiplier as needed
		data->angle_y -= (x - data->prev_x) * 0.01;
		
		// Store the current mouse position for the next movement event
		data->prev_x = x;
		data->prev_y = y;
    }

	if (data->img.mlx_img) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); // Libère l'image précédente
    }
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

    // t_point points[NB_POINTS] = {
    // {-100.0, 100.0, 0.0},
    // {0.0, 100.0, 0.0},
    // {100.0, 100.0, 0.0},
    // {-100.0, 0.0, 0.0},
    // {0.0, 0.0, 200.0},
    // {100.0, 0.0, 0.0},
    // {-100.0, -100.0, 0.0},
    // {0.0, -100.0, 0.0},
    // {100.0, -100.0, 0.0}
    // };

    t_point points[NB_POINTS] = {
        {-1.0, 1.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 1.0, 0.0},
        {-1.0, 0.0, 0.0},
        {0.0, 0.0, 2.0},
        {1.0, 0.0, 0.0},
        {-1.0, -1.0, 0.0},
        {1.0, -1.0, 0.0}
    };

    for (int i = 0; i < NB_POINTS; i++) {
        points[i].x *= 100;
        points[i].y *= 100;
        points[i].z *= 100;
    }

    for (int i = 0; i < NB_POINTS; i++)
		data.points[i] = points[i];

	data.zoom = 1.0;
	data.mouse_button = 0;

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_hook(data.win_ptr, 17, 0L, close, &data);

	mlx_hook(data.win_ptr, 4, 1L<<2, ft_mouse_down, &data);
	mlx_hook(data.win_ptr, 5, 1L<<3, ft_mouse_up, &data);
	mlx_hook(data.win_ptr, 6, 1L<<6, ft_mouse_move, &data);

	mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_loop_hook(data.mlx_ptr, &render, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}