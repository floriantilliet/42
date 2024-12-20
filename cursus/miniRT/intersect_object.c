/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_object.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 16:10:56 by ftilliet          #+#    #+#             */
/*   Updated: 2024/12/20 16:54:02 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

t_array *object_intersections(t_ray ray, t_objects *object)
{
    t_tuple object_to_ray;
    
    ray = transform_ray(ray, inverse4((*sphere).transformation));
    object_to_ray = substract_doubles(ray.origin, create_point(0, 0, 0)); //origin of sphere

    t_array *intersections = init_array(2);
    return(intersections);
}