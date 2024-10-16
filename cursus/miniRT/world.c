/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:03:23 by florian           #+#    #+#             */
/*   Updated: 2024/10/16 20:41:40 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_world *init_world(void)
{
    t_world *world;

    world = malloc(sizeof(t_world));
    if (!world)
        return (NULL);
    world->objects = init_objects();
    world->light = create_light(create_point(-10, 10, -10), create_point(1, 1, 1));
    return (world);
}