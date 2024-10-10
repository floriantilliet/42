/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:34:42 by florian           #+#    #+#             */
/*   Updated: 2024/10/10 11:51:44 by florian          ###   ########.fr       */
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

t_tuple multiply_tuple(t_tuple a, double b)
{
    t_tuple res;

    res.x = a.x * b;
    res.y = a.y * b;
    res.z = a.z * b;
    res.w = a.w * b;
    return (res);
}

t_tuple divide_tuple(t_tuple a, double b)
{
    t_tuple res;

    res.x = a.x / b;
    res.y = a.y / b;
    res.z = a.z / b;
    res.w = a.w / b;
    return (res);
}

double get_magnitude(t_tuple a)
{
    double res;

    res = sqrt(a.x * a.x + a.y * a.y + a.z * a.z);
    return (res);
}

t_tuple normalize_vector(t_tuple a)
{
    t_tuple res;
    double magnitude;

    magnitude = get_magnitude(a);
    res.x = a.x / magnitude;
    res.y = a.y / magnitude;
    res.z = a.z / magnitude;
    res.w = a.w / magnitude;
    return (res);
}

double scalar_product(t_tuple a, t_tuple b)
{
    double res;

    res = a.x * b.x + a.y * b.y + a.z * b.z;
    return (res);
}

t_tuple cross_product(t_tuple a, t_tuple b)
{
    t_tuple res;

    res = create_vector(a.y * b.z - a.z * b.y,
                        a.z * b.x - a.x * b.z,
                        a.x * b.y - a.y * b.x);
    return (res);
}