/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 19:31:59 by florian           #+#    #+#             */
/*   Updated: 2024/10/12 10:24:43 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	key_reset_and_close_hook(int keycode, t_data *data)
{
	if (keycode == XK_Escape)
		close_image(data);
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	key_reset_and_close_hook(keycode, data);
	return (0);
}

int	ft_create_trgb(unsigned char t, unsigned char r, unsigned char g,
		unsigned char b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

void	ft_pixel_put(t_img *img, unsigned int x, unsigned int y, int color)
{
	char	*dst;

	if (x <= WINDOW_WIDTH - 1 && y <= WINDOW_HEIGHT - 1)
	{
		dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
		*(unsigned int *)dst = color;
	}
}
#include <stdio.h>
int	main(int ac, char **av)
{
    t_data data;
    ac++;
    av++;
    // t_4matrix mat;
    // mat.mat[0][0] = 8;
    // mat.mat[0][1] = -5;
    // mat.mat[0][2] = 9;
    // mat.mat[0][3] = 2;
    // mat.mat[1][0] = 7;
    // mat.mat[1][1] = 5;
    // mat.mat[1][2] = 6;
    // mat.mat[1][3] = 1;
    // mat.mat[2][0] = -6;
    // mat.mat[2][1] = 0;
    // mat.mat[2][2] = 9;
    // mat.mat[2][3] = 6;
    // mat.mat[3][0] = -3;
    // mat.mat[3][1] = 0;
    // mat.mat[3][2] = -9;
    // mat.mat[3][3] = -4;
    
    // t_4matrix mat2 = inverse4(mat);
    // for (int i = 0; i < 4; i++) {
    //     for (int j = 0; j < 4; j++) {
    //         printf("%f ", mat2.mat[i][j]);
    //     }
    //     printf("\n");
    // }
    t_tuple point;
    point = create_point(1,0,1);
    t_4matrix mat;
    mat = scaling_mat(5,5,5);
    t_tuple point2 =mat_tuple_product(mat, point);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            printf("%f ", mat.mat[i][j]);
        }
        printf("\n");
    }
    
    printf("Transformed point: (%f, %f, %f, %f)\n", point2.x, point2.y, point2.z, point2.w);
    int color = ft_create_trgb(0, 255, 255, 255);
    ft_init_image(&data);
    ft_pixel_put(&data.img, 0, 0, color);
    ft_pixel_put(&data.img, 1, 1, color);
    ft_pixel_put(&data.img, 2, 2, color);
    ft_pixel_put(&data.img, 3, 3, color);
    ft_pixel_put(&data.img, 4, 4, color);
    ft_pixel_put(&data.img, 5, 5, color);
    ft_pixel_put(&data.img, 6, 6, color);
    ft_pixel_put(&data.img, 7, 7, color);
    ft_pixel_put(&data.img, 8, 8, color);
    ft_pixel_put(&data.img, 9, 9, color);
    ft_pixel_put(&data.img, 10, 10, color);
    mlx_put_image_to_window((&data)->mlx_ptr, (&data)->win_ptr, (&data)->img.mlx_img, 0, 0);
    mlx_hook((&data)->win_ptr, KeyPress, KeyPressMask, &key_hook, (&data));
	mlx_hook((&data)->win_ptr, 17, 0L, close_image, (&data));
    mlx_loop((&data)->mlx_ptr);
}