/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:22:08 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:49:24 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

double	rad(double deg)
{
	return (deg * DEG_TO_RAD);
}

t_point	ft_multiply_vector_by_matrix(t_point *v, t_matrix m)
{
	t_point	res;

	res.x = v->x * m.i.x + v->y * m.i.y + v->z * m.i.z;
	res.y = v->x * m.j.x + v->y * m.j.y + v->z * m.j.z;
	res.z = v->x * m.k.x + v->y * m.k.y + v->z * m.k.z;
	return (res);
}

t_matrix	ft_get_rot_matrix(double deg, char axis)
{
	if (axis == 'x')
		return ((t_matrix){(t_point){1., 0., 0.}, (t_point){0., cos(rad(deg)),
			-sin(rad(deg))}, (t_point){0., sin(rad(deg)), cos(rad(deg))}});
	if (axis == 'y')
		return ((t_matrix){(t_point){cos(rad(deg)), 0., -sin(rad(deg))},
			(t_point){0., 1., 0.}, (t_point){sin(deg), 0., cos(rad(deg))}});
	if (axis == 'z')
		return ((t_matrix){(t_point){cos(rad(deg)), -sin(rad(deg)), 0.},
			(t_point){sin(rad(deg)), cos(rad(deg)), 0.}, (t_point){0., 0.,
			1.}});
	return ((t_matrix){
		(t_point){1., 0., 0.},
		(t_point){0., 1., 0.},
		(t_point){0., 0., 1.},
	});
}
