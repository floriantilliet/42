/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:00:48 by florian           #+#    #+#             */
/*   Updated: 2024/10/13 21:24:28 by florian          ###   ########.fr       */
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