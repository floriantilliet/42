/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:00:14 by florian           #+#    #+#             */
/*   Updated: 2024/10/18 14:12:23 by florian          ###   ########.fr       */
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

t_objects	*create_object(t_tuple origin)
{
	t_objects	*new_object;

	new_object = malloc(sizeof(t_objects));
	if (!new_object)
		return (NULL);
	new_object->origin = origin;
    new_object->transformation = identity4();
    new_object->material = create_material(create_vector(1, 1, 1), 0.1, 0.9, 0.9, 200);
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
    float a;
    float b;
    float c;
    float discriminant;
    t_tuple sphere_to_ray;
    
    ray = transform_ray(ray, inverse4((*sphere).transformation));
    sphere_to_ray = substract_floats(ray.origin, (*sphere).origin);
    a = scalar_product(ray.direction, ray.direction);
    b = 2 * scalar_product(ray.direction, sphere_to_ray);
    c = scalar_product(sphere_to_ray, sphere_to_ray) - 1;
    discriminant = b * b - 4 * a * c;
    if (discriminant < 0)
    {
        return(NULL);
    }
    else
    {
        // printf("Two intersections\n");
        t_array *intersections = initArray(2);
        insertArray(intersections, (-b - sqrt(discriminant)) / (2 * a));
        insertArray(intersections, (-b + sqrt(discriminant)) / (2 * a));
        return(intersections);
    }
}

t_tuple sphere_normal(t_objects *sphere, t_tuple world_point)
{
    t_tuple object_point;
    t_tuple object_normal;
    t_tuple world_normal;
    
    object_point = mat_tuple_product(inverse4((*sphere).transformation), world_point);
    object_normal = substract_floats(object_point, create_point(0, 0, 0));
    world_normal = mat_tuple_product(mat_transpose(inverse4((*sphere).transformation)), object_normal);
    world_normal.w = 0;
    return(normalize_vector(world_normal));
}

t_tuple sphere_reflect(t_tuple in, t_tuple normal)
{
    t_tuple res;
    
    res = substract_floats(in, multiply_tuple(normal, 2 * scalar_product(in, normal)));
    return(res);
}