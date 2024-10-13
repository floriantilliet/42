/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:18:39 by florian           #+#    #+#             */
/*   Updated: 2024/10/13 21:12:58 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

t_tuple add_colors(t_tuple color1, t_tuple color2)
{
    t_tuple result;

    result.x = color1.x + color2.x;
    result.y = color1.y + color2.y;
    result.z = color1.z + color2.z;
    return (result);
}

t_tuple substract_colors(t_tuple color1, t_tuple color2)
{
    t_tuple result;

    result.x = color1.x - color2.x;
    result.y = color1.y - color2.y;
    result.z = color1.z - color2.z;
    return (result);
}

t_tuple multiply_color(t_tuple color, double scalar)
{
    t_tuple result;

    result.x = color.x * scalar;
    result.y = color.y * scalar;
    result.z = color.z * scalar;
    return (result);
}

t_tuple color_product(t_tuple color1, t_tuple color2)
{
    t_tuple result;

    result.x = color1.x * color2.x;
    result.y = color1.y * color2.y;
    result.z = color1.z * color2.z;
    return (result);
}

int tuple_to_trgb(t_tuple color)
{
    int t;
    int r;
    int g;
    int b;

    t = 0;
    r = (int)(color.x * 255.0);
    g = (int)(color.y * 255.0);
    b = (int)(color.z * 255.0);
    return (ft_create_trgb(t, r, g, b));
}

// int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g,
// 		unsigned char b)
// {
// 	return ((t << 24) | (r << 16) | (g << 8) | b);
// }

// void	ft_pixel_put(t_img *img, unsigned int x, unsigned int y, int color)
// {
// 	char	*dst;

// 	if (x <= WINDOW_WIDTH - 1 && y <= WINDOW_HEIGHT - 1)
// 	{
// 		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
// 		*(unsigned int *)dst = color;
// 	}
// }