/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:34:42 by florian           #+#    #+#             */
/*   Updated: 2024/10/10 11:20:34 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_tuple create_vector(double x, double y, double z)
{
    t_tuple vector;

    vector.x = x;
    vector.y = y;
    vector.z = z;
    vector.w = 0;
    return (vector);
}

t_tuple create_point(double x, double y, double z)
{
    t_tuple point;

    point.x = x;
    point.y = y;
    point.z = z;
    point.w = 1;
    return (point);
}

int floats_equal(double a, double b)
{
    if (fabs(a - b) < EPSILON)
        return (1);
    return (0);
}

t_tuple add_floats(t_tuple a, t_tuple b)
{
    t_tuple res;

    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    res.w = a.w + b.w;
    return (res);
}

t_tuple substract_floats(t_tuple a, t_tuple b)
{
    t_tuple res;

    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    res.w = a.w - b.w;
    return (res);
}

t_tuple negate_tuple(t_tuple a)
{
    t_tuple res;

    res.x = -a.x;
    res.y = -a.y;
    res.z = -a.z;
    res.w = -a.w;
    return (res);
}

t_tuple scalar_product(t_tuple a, double b)
{
    t_tuple res;

    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    res.w = a.w * b;
    return (res);
}

t_tuple scalar_division(t_tuple a, double b)
{
    t_tuple res;

    res.x = a.x / b;
    res.y = a.y / b;
    res.z = a.z / b;
    res.w = a.w / b;
    return (res);
}