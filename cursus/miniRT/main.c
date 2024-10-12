/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:59 by florian           #+#    #+#             */
/*   Updated: 2024/10/13 00:46:40 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	key_reset_and_close_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_image(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	key_reset_and_close_hook(keycode, data);
	return (0);
}

int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

void	ft_pixel_put(t_img *img, unsigned int x, unsigned int y, int color)
{
	char	*dst;

	if (x <= WINDOW_WIDTH - 1 && y <= WINDOW_HEIGHT - 1)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	main(int ac, char **av)
{
    t_data data;
    ac++;
    av++;
    
    t_intersections **intersections;
    t_objects **objects;
    t_objects *new_object;
    
    intersections = init_intersections();
    objects = init_objects();
    new_object = create_object(create_point(0, 0, 0), intersections);
    add_object(objects, new_object);
    // add_transformation(new_object, translation_mat(5, 0, 0));
    // sphere_intersections(create_ray(create_point(0, 0, -5), create_vector(0, 0, 1)), new_object);

    // print_intersections(new_object->intersections);
    
    int color = ft_create_trgb(0, 255, 0, 0);
    ft_init_image(&data);

    int y = 0;
    int x = 0;
    float world_y;
    float world_x;
    int wall_size = 7;
    int pixel_size =wall_size / WINDOW_WIDTH;
    while (y < WINDOW_HEIGHT - 1)
    {
        world_y = (WINDOW_HEIGHT / 2) - y * pixel_size;
        while (x < WINDOW_WIDTH - 1)
        {
            world_x = x * pixel_size - (WINDOW_WIDTH / 2);
            printf("x: %f, y: %f\n", world_x, world_y);
            t_tuple position = create_point(world_x, world_y, 10);
            t_ray ray = create_ray(create_point(0, 0, -5), normalize_vector(substract_floats(position, create_point(0, 0, -5))));
            sphere_intersections(ray, new_object);
            if (new_object->intersections)
                ft_pixel_put(&data.img, world_x, world_y, color);
            x++;
        }
        y++;
    }
    
    ft_pixel_put(&data.img, 1, 1, color);
    // ft_pixel_put(&data.img, 2, 2, color);
    // ft_pixel_put(&data.img, 3, 3, color);
    // ft_pixel_put(&data.img, 4, 4, color);
    // ft_pixel_put(&data.img, 5, 5, color);
    // ft_pixel_put(&data.img, 6, 6, color);
    // ft_pixel_put(&data.img, 7, 7, color);
    // ft_pixel_put(&data.img, 8, 8, color);
    // ft_pixel_put(&data.img, 9, 9, color);
    // ft_pixel_put(&data.img, 10, 10, color);
    mlx_put_image_to_window((&data)->mlx_ptr, (&data)->win_ptr, (&data)->img.mlx_img, 0, 0);
    mlx_hook((&data)->win_ptr, KeyPress, KeyPressMask, &key_hook, (&data));
	mlx_hook((&data)->win_ptr, 17, 0L, close_image, (&data));
    mlx_loop((&data)->mlx_ptr);
}