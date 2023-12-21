/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:20:50 by florian           #+#    #+#             */
/*   Updated: 2023/12/21 17:49:35 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "graphics.h"

int close_image(t_data *img)
{
    mlx_destroy_window(img->mlx_ptr, img->win_ptr);
    exit(1);
    return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		close_image(data);
		data->win_ptr = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	render(t_data *data)
{   
    t_data  proj;
	int x;
	
	if (data->win_ptr == NULL)
		return (1);

	if (data->img.mlx_img) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); // Libère l'image précédente
    }
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

    proj = ft_iso_projection(data);

    ft_draw(data, proj);

	x = 0;
	while (x<data->width)
	{
		free(proj.map[x]);
		x++;
	}
	free(proj.map);

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

	return (0);
}


int	ft_mouse_down(int button, int x, int y, t_data *data)
{	
	if (button == 4)
		data->zoom += 0.1;
	
	if (button == 5)
		data->zoom -= 0.1;

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
	// printf("mouse button: %d\n", data->mouse_button);
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
	return (0);
}

int	main(int ac, char **av)
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

	int fd;
    char **tab;
    char ***tabs;

    if (ac != 2)
        return (0);
    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (0);
    tab = fd_to_tab(fd);
    if (!tab)
        return (0);
    tabs = tab_to_tabs(tab);
    if (!tabs)
        return (0);
    data.map = tabs_to_map(tabs);
    if (!data.map)
	{
        return (0);
	}
	get_limits(&data);
	printf("width: %f, height: %f, floor: %f, ceiling: %f\n", data.width, data.height, data.floor, data.ceiling);
	int i = 0;
    int j;
    while (data.map[i])
    {
        j = 0;
        while (data.map[i][j].x != -1)
        {
            data.map[i][j].x *= 10;
			data.map[i][j].y *= 10;
			data.map[i][j].z *= 10;
			// printf("x: %f, y: %f, z: %f\n", data.map[i][j].x, data.map[i][j].y, data.map[i][j].z);
            j++;
        }
        i++;
    }
	data.zoom = 1.0;
	data.mouse_button = 0;

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_hook(data.win_ptr, 17, 0L, close_image, &data);

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