/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:03:23 by florian           #+#    #+#             */
/*   Updated: 2024/11/04 16:06:44 by florian          ###   ########.fr       */
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