/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:59 by florian           #+#    #+#             */
/*   Updated: 2024/10/29 15:01:02 by florian          ###   ########.fr       */
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
    
    // t_objects **objects;
    t_objects *new_object;
    t_world *world;
    
    world = init_world();
    world->objects = init_objects();
    new_object = create_object(identity4(), create_material(create_vector(0.8, 1.0, 0.6), 0.1, 0.7, 0.2, 200));
    add_object(world->objects, new_object);
    new_object = create_object(scaling_mat(0.5, 0.5, 0.5), create_material(create_vector(0.2, 1, 0.2), 0.1, 0.9, 0.9, 200));
    add_object(world->objects, new_object);
    // new_object->transformation = translation_mat(-1.5, 1.5, 5);
    
    t_light light = create_light(create_point(-10, 10, -10), create_point(1, 1, 1));
    // t_tuple eyev = create_vector(0, 0, -1);
    // t_tuple normalv = create_vector(0, 0, -1);
    
    // t_tuple result = lighting(new_object->material, light, create_point(0, 0, 0), eyev, normalv);
    // printf("r: %f, g: %f, b: %f\n", result.x, result.y, result.z);  
    
    t_array *xs2;
    xs2 = init_array(2);
    xs2 = intersect_world(create_ray(create_point(0, 0, -5), create_vector(0, 0, 1)), world);
    print_array(xs2);
    
    ft_init_image(&data);

    int y = 0;
    int x = 0;
    float world_y;
    float world_x;
    float wall_size = 7;
    float pixel_size =wall_size / WINDOW_WIDTH;
    t_array *xs = init_array(2);
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
            xs = sphere_intersections(ray, new_object);
            if (hit_array(xs) != -1)
            {
                t_tuple normal = sphere_normal(new_object, get_position(ray, hit_array(xs)));
                t_tuple eye = multiply_tuple(ray.direction, -1);
                t_tuple col = lighting(new_object->material, light, position, eye, normal);
                int color = tuple_to_trgb(col);
                ft_pixel_put(&data.img, x, y, color);
            }
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