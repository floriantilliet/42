/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/31 17:30:02 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:49:17 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

void	ft_pixel_put(t_img *img, unsigned int x, unsigned int y, int color)
{
	char	*dst;

	if (x <= WINDOW_WIDTH - 1 && y <= WINDOW_HEIGHT - 1)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

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