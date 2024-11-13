/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 09:38:12 by florian           #+#    #+#             */
/*   Updated: 2024/11/13 11:12:42 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

// int is_shadowed(t_world *world, t_tuple point)
// {
//     t_tuple v;
//     double distance;
//     t_tuple direction;
//     t_ray r;
//     t_array *intersections;
//     t_intersection *hit;

//     v = substract_tuples(world->light->position, point);
//     distance = get_magnitude(v);
//     direction = normalize_vector(v);
    
//     r = create_ray(point, direction);
//     intersections = intersect_world(world, r);
    
//     hit = hit_array(intersections);
//     if (hit && hit->t < distance)
//         return (1);
//     return (0);
// }