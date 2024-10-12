/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rays.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/12 10:49:03 by florian           #+#    #+#             */
/*   Updated: 2024/10/12 11:00:00 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_ray	create_ray(t_tuple origin, t_tuple direction)
{
    t_ray	ray;

    ray.origin = origin;
    ray.direction = direction;
    return (ray);
}

t_tuple	get_position(t_ray ray, double t)
{
    t_tuple	res;

    res = add_floats(ray.origin, multiply_tuple(ray.direction, t));
    return (res);
}