/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:00:48 by florian           #+#    #+#             */
/*   Updated: 2024/11/11 21:58:04 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_light	create_light(t_tuple position, t_tuple intensity)
{
	t_light	light;

	light.position = position;
	light.intensity = intensity;
	return (light);
}

t_material	create_material(t_tuple color, double ambient, double diffuse,
		double specular, double shininess)
{
	t_material	material;

	material.color = color;
	material.ambient = ambient;
	material.diffuse = diffuse;
	material.specular = specular;
	material.shininess = shininess;
	return (material);
}

t_tuple	lighting(t_material material, t_light light, t_tuple point,
		t_tuple eye_vector, t_tuple normal_vector)
{
	t_tuple effective_color = color_product(material.color, light.intensity);
	t_tuple lightv = normalize_vector(substract_doubles(light.position, point));
	t_tuple ambient = multiply_color(effective_color, material.ambient);

	double light_dot_normal = scalar_product(lightv, normal_vector);
	t_tuple diffuse;
	t_tuple specular;
	if (light_dot_normal < 0)
	{
		diffuse = create_vector(0, 0, 0);
		specular = create_vector(0, 0, 0);
	}
	else
	{
		diffuse = multiply_color(effective_color, material.diffuse
				* light_dot_normal);
		t_tuple reflectv = sphere_reflect(multiply_tuple(lightv, -1),
				normal_vector);
		double reflect_dot_eye = scalar_product(reflectv, eye_vector);
		if (reflect_dot_eye <= 0)
		{
			specular = create_vector(0, 0, 0);
		}
		else
		{
			double factor = pow(reflect_dot_eye, material.shininess);
			specular = multiply_color(light.intensity, material.specular
					* factor);
		}
	}
	return (add_colors(add_colors(ambient, diffuse), specular));
}