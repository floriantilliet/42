/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:59 by florian           #+#    #+#             */
/*   Updated: 2024/10/14 12:14:47 by florian          ###   ########.fr       */
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
    
    new_object-> material = create_material(create_point(1, 0.2, 1), 0.1, 0.9, 0.9, 200);
    t_light light = create_light(create_point(-10, 10, -10), create_point(1, 1, 1));
    
    int color = ft_create_trgb(0, 255, 0, 0);
    ft_init_image(&data);

    int y = 0;
    int x = 0;
    float world_y;
    float world_x;
    float wall_size = 7;
    float pixel_size =wall_size / WINDOW_WIDTH;
    while (y < WINDOW_HEIGHT - 1)
    {
        world_y = (wall_size / 2) - y * pixel_size;
        x = 0;
        while (x < WINDOW_WIDTH - 1)
        {
            world_x = - (wall_size/2) + x * pixel_size;
            t_tuple position = create_point(world_x, world_y, 10);
            t_tuple ray_origin = create_point(0, 0, -5);
            t_ray ray = create_ray(ray_origin, normalize_vector(substract_floats(position, ray_origin)));
            t_tuple normal = sphere_normal(new_object, position);
            t_tuple eye = multiply_tuple(ray.direction, -1);
            t_tuple col = lighting(new_object->material, light, position, eye, normal);
            color = tuple_to_trgb(col);
            if (sphere_intersections(ray, new_object))
                ft_pixel_put(&data.img, x, y, color);
            // if (hit(new_object->intersections))
                // ft_pixel_put(&data.img, x, y, color);
            x++;
        }
        y++;
    }
    printf("Done\n");
    // ft_pixel_put(&data.img, 1, 1, color);
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