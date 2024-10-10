/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:34:42 by florian           #+#    #+#             */
/*   Updated: 2024/10/10 10:37:25 by florian          ###   ########.fr       */
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