/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:59 by florian           #+#    #+#             */
/*   Updated: 2024/11/10 13:38:32 by florian          ###   ########.fr       */
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
    new_object = create_object(scaling_mat(10, 0.01, 10), create_material(create_vector(1, 0.9, 0.9), 0.1, 0.9, 0, 200));
    add_object(world->objects, new_object);
    t_4matrix transform; 
    transform = mat_product(translation_mat(0, 0, 5), rotation_y_mat(-PI/4));
    transform = mat_product(transform, rotation_x_mat(PI/2));
    transform = mat_product(transform, scaling_mat(10, 0.01, 10));
    new_object = create_object(transform, create_material(create_vector(1, 0.9, 0.9), 0.1, 0.9, 0, 200));
    add_object(world->objects, new_object);
    transform = mat_product(translation_mat(0, 0, 5), rotation_y_mat(PI/4));
    transform = mat_product(transform, rotation_x_mat(PI/2));
    transform = mat_product(transform, scaling_mat(10, 0.01, 10));
    new_object = create_object(transform, create_material(create_vector(1, 0.9, 0.9), 0.1, 0.9, 0, 200));    // new_object->transformation = translation_mat(-1.5, 1.5, 5);
    add_object(world->objects, new_object);
    new_object = create_object(translation_mat(-0.5, 1, 0.5), create_material(create_vector(0.1, 1, 0.5), 0.1, 0.7, 0.3, 200));
    add_object(world->objects, new_object);
    new_object = create_object(mat_product(translation_mat(1.5, 0.5, -0.5), scaling_mat(0.5, 0.5, 0.5)), create_material(create_vector(0.5, 1, 0.1), 0.1, 0.7, 0.3, 200));
    add_object(world->objects, new_object);
    new_object = create_object(mat_product(translation_mat(-1.5, 0.33, -0.75), scaling_mat(0.3, 0.33, 0.33)), create_material(create_vector(1, 0.8, 0.1), 0.1, 0.7, 0.3, 200));
    add_object(world->objects, new_object);
    
    t_camera camera;
    camera = create_camera(WINDOW_HEIGHT, WINDOW_WIDTH, 2*PI/3);
    camera.transform = view_transform(create_point(0, 1.5, -5), create_point(0, 1, 0), create_vector(0, 1, 0));
    ft_init_image(&data);
    render(world, camera, data);
    // int y = 0;
    // int x = 0;
    // float world_y;
    // float world_x;
    // float wall_size = 7;
    // float pixel_size =wall_size / WINDOW_WIDTH;
    // t_array *xs = init_array(2);
    // while (y < WINDOW_HEIGHT - 1)
    // {
    //     world_y = (wall_size / 2) - y * pixel_size;
    //     x = 0;
    //     while (x < WINDOW_WIDTH - 1)
    //     {
    //         world_x = - (wall_size/2) + x * pixel_size;
    //         t_tuple position = create_point(world_x, world_y, 10);
    //         t_tuple ray_origin = create_point(0, 0, -5);
    //         t_ray ray = create_ray(ray_origin, normalize_vector(substract_floats(position, ray_origin)));
    //         xs = sphere_intersections(ray, new_object);
    //         if (hit_array(xs) != -1)
    //         {
    //             t_tuple normal = sphere_normal(new_object, get_position(ray, hit_array(xs)));
    //             t_tuple eye = multiply_tuple(ray.direction, -1);
    //             t_tuple col = lighting(new_object->material, light, position, eye, normal);
    //             int color = tuple_to_trgb(col);
    //             ft_pixel_put(&data.img, x, y, color);
    //         }
    //         x++;
    //         }
    //     y++;
    // }  
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