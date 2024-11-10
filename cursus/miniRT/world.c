/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:03:23 by florian           #+#    #+#             */
/*   Updated: 2024/11/10 13:40:49 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_world *init_world(void)
{
    t_world *world;

    world = malloc(sizeof(t_world));
    if (!world)
        return (NULL);
    world->objects = init_objects();
    world->light = create_light(create_point(-10, 10, -10), create_point(1, 1, 1));
    return (world);
}

t_array *intersect_world(t_ray ray, t_world *world)
{
    t_objects *current;
    t_array *intersections;

    intersections = init_array(2);
    current = *world->objects;
    while (current != NULL)
    {
        intersections = concatenate_array(intersections, sphere_intersections(ray, current));
        current = current->next;
    }
    sort_array(intersections);
    return (intersections);
}

t_computations prepare_computations(t_intersection intersection, t_ray ray)
{
    t_computations comps;
    
    comps.t = intersection.t;
    comps.object = intersection.object;
    comps.point = get_position(ray, comps.t);
    comps.eyev = multiply_tuple(ray.direction, -1);
    comps.normalv = sphere_normal(comps.object, comps.point);
    if (scalar_product(comps.normalv, comps.eyev) < 0)
    {
        comps.inside = 1;
        comps.normalv = multiply_tuple(comps.normalv, -1);
    }
    else
        comps.inside = 0;
    return(comps);
}

t_tuple shade_hit(t_world *world, t_computations comps)
{
    return (lighting(comps.object->material, world->light, comps.point, comps.eyev, comps.normalv));
}

t_tuple color_at(t_world *world, t_ray ray)
{
    t_array *intersections;
    t_computations comps;
    t_tuple color;

    intersections = intersect_world(ray, world);
    if (hit_array(intersections) == -1)
        return (create_point(1, 0, 0));
    comps = prepare_computations(intersections->array[0], ray);
    color = shade_hit(world, comps);
    // printf("Color: %f %f %f\n", color.x, color.y, color.z);
    return (color);
}

t_4matrix view_transform(t_tuple from, t_tuple to, t_tuple up)
{
    t_tuple forward;
    t_tuple upn;
    t_tuple left;
    t_tuple true_up;
    t_4matrix orientation;

    forward = normalize_vector(substract_floats(to, from));
    upn = normalize_vector(up);
    left = cross_product(forward, upn);
    true_up = cross_product(left, forward);
    orientation = identity4();
    orientation.mat[0][0] = left.x;
    orientation.mat[0][1] = left.y;
    orientation.mat[0][2] = left.z;
    orientation.mat[1][0] = true_up.x;
    orientation.mat[1][1] = true_up.y;
    orientation.mat[1][2] = true_up.z;
    orientation.mat[2][0] = -forward.x;
    orientation.mat[2][1] = -forward.y;
    orientation.mat[2][2] = -forward.z;
    return (mat_product(orientation, translation_mat(-from.x, -from.y, -from.z)));
}

t_camera create_camera(float hsize, float vsize, float field_of_view)
{
    t_camera camera;
    float half_view;
    float aspect;
    
    camera.hsize = hsize;
    camera.vsize = vsize;
    camera.field_of_view = field_of_view;
    camera.transform = identity4();
    half_view = tan(camera.field_of_view / 2);
    aspect = camera.hsize / camera.vsize;
    if (aspect >= 1)
    {
        camera.half_width = half_view;
        camera.half_height = half_view / aspect;
    }
    else
    {
        camera.half_width = half_view * aspect;
        camera.half_height = half_view;
    }
    camera.pixel_size = (camera.half_width * 2) / camera.hsize;
    return (camera);
}

t_ray ray_for_pixel(t_camera camera, float px, float py)
{
    float xoffset;
    float yoffset;
    float world_x;
    float world_y;
    t_tuple pixel;
    t_tuple origin;
    t_tuple direction;

    xoffset = (px + 0.5) * camera.pixel_size;
    yoffset = (py + 0.5) * camera.pixel_size;
    world_x = camera.half_width - xoffset;
    world_y = camera.half_height - yoffset;
    pixel = mat_tuple_product(inverse4(camera.transform), create_point(world_x, world_y, -1));
    origin = mat_tuple_product(inverse4(camera.transform), create_point(0, 0, 0));
    direction = normalize_vector(substract_floats(pixel, origin));
    return (create_ray(origin, direction));
}

void render(t_world *world, t_camera camera, t_data data)
{
    int x;
    int y;
    int color;
    t_ray ray;

    y = 0;
    while (y < camera.vsize)
    {
        x = 0;
        while (x < camera.hsize)
        {
            ray = ray_for_pixel(camera, x, y);
            color = tuple_to_trgb(color_at(world, ray));
            // printf("x: %d y: %d\n", x, y);
            ft_pixel_put(&data.img, x, y, color);
            x++;
        }
        y++;
    }
}