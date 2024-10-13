/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spheres.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 12:00:14 by florian           #+#    #+#             */
/*   Updated: 2024/10/13 11:19:17 by florian          ###   ########.fr       */
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

t_objects	*create_object(t_tuple origin, t_intersections **intersections)
{
	t_objects	*new_object;

	new_object = malloc(sizeof(t_objects));
	if (!new_object)
		return (NULL);
	new_object->origin = origin;
    new_object->intersections = intersections;
    new_object->transformation = identity4();
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

void sphere_intersections(t_ray ray, t_objects *sphere)
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
        // printf("No intersection\n");
    }
    else
    {
        // printf("Two intersections\n");
        add_intersection((*sphere).intersections, create_intersection((-b - sqrt(discriminant)) / (2 * a)));
        add_intersection((*sphere).intersections, create_intersection((-b + sqrt(discriminant)) / (2 * a)));
    }
}
