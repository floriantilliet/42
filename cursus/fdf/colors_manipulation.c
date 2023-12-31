/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:29:58 by florian           #+#    #+#             */
/*   Updated: 2023/12/31 17:30:00 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	get_color(double z, double min_altitude, double max_altitude)
{
	if (z < min_altitude)
		return (0);
	if (z > max_altitude)
		return (255);

	double range = max_altitude - min_altitude;
	double normalized_z = (z - min_altitude) / range;

	int red = 255 - (normalized_z * 255);
	int green = normalized_z * 255;
	int blue = 255;

	return (ft_create_trgb(0, red, green, blue));
}