/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:00:14 by florian           #+#    #+#             */
/*   Updated: 2024/11/11 21:21:30 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_objects	**init_objects(void)
{
	t_objects **objects;

	objects = malloc(sizeof(t_objects *));
	if (!objects)
		return (NULL);
	*objects = NULL;
	return (objects);
}

t_objects	*create_object(t_4matrix transformation, t_material material)
{
	t_objects	*new_object;

	new_object = malloc(sizeof(t_objects));
	if (!new_object)
		return (NULL);
    new_object->transformation = transformation;
    new_object->material = material;
	return (new_object);
}

void	add_object(t_objects **objects, t_objects *new_objects)
{
	t_objects    *current;

	if (*objects == NULL)
		*objects = new_objects;
	else
	{
		current = *objects;
		while (current->next != NULL)
			current = current->next;
		current->next = new_objects;
	}
}

void    add_transformation(t_objects *object, t_4matrix transformation)
{
    (*object).transformation = mat_product((*object).transformation, transformation);
}

t_array *sphere_intersections(t_ray ray, t_objects *sphere)
{
    double a;
    double b;
    double c;
    double discriminant;
    t_tuple sphere_to_ray;
    
    ray = transform_ray(ray, inverse4((*sphere).transformation));
    sphere_to_ray = substract_doubles(ray.origin, create_point(0, 0, 0)); //origin of sphere
    a = scalar_product(ray.direction, ray.direction);
    b = 2 * scalar_product(ray.direction, sphere_to_ray);
    c = scalar_product(sphere_to_ray, sphere_to_ray) - 1;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        t_array *intersections = init_array(2);
        return(intersections);
    }
    else
    {
        t_array *intersections = init_array(2);
        insert_array(intersections, (-b - sqrt(discriminant)) / (2 * a), sphere);
        insert_array(intersections, (-b + sqrt(discriminant)) / (2 * a), sphere);
        return(intersections);
    }
}

t_tuple sphere_normal(t_objects *sphere, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;
    
    object_point = mat_tuple_product(inverse4((*sphere).transformation), world_point);
    object_normal = substract_doubles(object_point, create_point(0, 0, 0));
    world_normal = mat_tuple_product(mat_transpose(inverse4((*sphere).transformation)), object_normal);
    world_normal.w = 0;
    return(normalize_vector(world_normal));
}

t_tuple sphere_reflect(t_tuple in, t_tuple normal)
{
    t_tuple res;
    
    res = substract_doubles(in, multiply_tuple(normal, 2 * scalar_product(in, normal)));
    return(res);
}