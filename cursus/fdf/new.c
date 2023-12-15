/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/15 10:0NB_POINTS:14 by ftilliet          #+#    #+#             */
/*   Updated: 2023/12/15 14:03:51 by ftilliet         ###   ########.fr       */
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
    int color;

	if (data->win_ptr == NULL)
		return (1);

    proj = ft_iso_projection(data);
    
    color = ft_create_trgb(0,255,0,0);
    color = ft_get_opposite(color);
    color = ft_add_shade(0.5,color);

    ft_draw_image(data, proj, color);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	int color;
	const int move_step = 10; // Tu peux ajuster la distance de déplacement

	if (keycode == XK_Up) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
		// Déplace l'image vers le haut
		for (int i = 0; i < NB_POINTS; i++)
        {
			data->points[i].y -= move_step;
            data->points[i].x -= move_step;
        }
	}
	
	else if (keycode == XK_Down) // Remplace KEY_DOWN par la valeur correspondant à la touche souhaitée
	{
		// Déplace l'image vers le bas
		for (int i = 0; i < NB_POINTS; i++)
        {
            data->points[i].y += move_step;
            data->points[i].x += move_step;
        }
	}

	if (keycode == XK_Left) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
		// Déplace l'image vers le haut
		for (int i = 0; i < NB_POINTS; i++)
        {
            data->points[i].x -= move_step;
            data->points[i].y += move_step;
        
        }
	}

	if (keycode == XK_Right)
	{
		// Déplace l'image vers le haut
		for (int i = 0; i < NB_POINTS; i++)
        {
            data->points[i].x += move_step;
            data->points[i].y -= move_step;
        }
	}

	if (keycode == XK_d)
	{
    	for (int i = 0; i < NB_POINTS; i++)
    	{
        	data->angle_y -= 0.001;
    	}
	}

	if (keycode == XK_a)
	{
    	for (int i = 0; i < NB_POINTS; i++)
		{
			data->angle_y += 0.001;
		}
	}

    if (keycode == XK_w)
    {
    	for (int i = 0; i < NB_POINTS; i++)
    	{
        	data->angle_x += 0.001;
    	}
    }

    if (keycode == XK_s)
    {
    	for (int i = 0; i < NB_POINTS; i++)
    	{
        	data->angle_x -= 0.001;
    	}
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

	t_point P0, P1, P2, P3, P4, P5, P6, P7, P8;
    t_point proj0, proj1, proj2, proj3, proj4, proj5, proj6, proj7, proj8;

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

	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
    mlx_hook(data.win_ptr, 17, 0L, close, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);
    mlx_loop_hook(data.mlx_ptr, &render, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}