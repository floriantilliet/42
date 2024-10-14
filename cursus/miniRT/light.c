/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:00:48 by florian           #+#    #+#             */
/*   Updated: 2024/10/14 12:05:46 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_light create_light(t_tuple position, t_tuple intensity)
{
    t_light light;

    light.position = position;
    light.intensity = intensity;
    return (light);
}

t_material create_material(t_tuple color, float ambient, float diffuse, float specular, float shininess)
{
    t_material material;

    material.color = color;
    material.ambient = ambient;
    material.diffuse = diffuse;
    material.specular = specular;
    material.shininess = shininess;
    return (material);
}

t_tuple lighting(t_material material, t_light light, t_tuple point, t_tuple eye_vector, t_tuple normal_vector)
{
    t_tuple effective_color;
    t_tuple light_vector;
    float light_dot_normal;
    t_tuple diffuse;
    t_tuple specular;
    t_tuple reflect_vector;
    float reflect_dot_eye;
    float factor;
    
    effective_color = color_product(material.color, light.intensity);
    light_vector = normalize_vector(substract_floats(light.position, point));
    effective_color = multiply_color(effective_color, material.ambient);

    light_dot_normal = scalar_product(light_vector, normal_vector);
    if (light_dot_normal < 0)
    {
        diffuse = create_vector(0, 0, 0);
        specular = create_vector(0, 0, 0);
    }
    else 
    {
        diffuse = multiply_color(effective_color, material.diffuse * light_dot_normal);
        reflect_vector = sphere_reflect(multiply_tuple(light_vector, -1), normal_vector);
        reflect_dot_eye = scalar_product(reflect_vector, eye_vector);
        if (reflect_dot_eye <= 0)
            specular = create_vector(0, 0, 0);
        else
        {
            factor = pow(reflect_dot_eye, material.shininess);
            specular = multiply_color(light.intensity, material.specular * factor);
        }        
    }
    return(add_colors(add_colors(diffuse, specular), effective_color));
}