#include <stdio.h>
#include "graphics.h"

#define WINDOW_WIDTH 1920
#define WINDOW_HEIGHT 1080

#define MLX_ERROR 1

int close(t_data *img)
{
    mlx_destroy_window(img->mlx_ptr, img->win_ptr);
    exit(1);
    return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == XK_Escape)
	{
		close(data);
		data->win_ptr = NULL;
	}
	printf("Keypress: %d\n", keysym);
	return (0);
}

int	handle_keyrelease(int keysym, void *data)
{
    printf("Keyrelease: %d\n", keysym);
    return (0);
}

int	render(t_data *data)
{
    int i;
    int j;
    int color;

	t_point P0;
	t_point P1;
	t_point P2;
	t_point P3;
	t_point P4;
	t_point P5;
	t_point P6;
	t_point P7;
	t_point P8;

	P0.x = 300, P0.y = 300, P0.z = 0;
	P1.x = 400, P1.y = 300, P1.z = 0;
	P2.x = 500, P2.y = 300, P2.z = 0;
	P3.x = 300, P3.y = 400, P3.z = 0;
	P4.x = 400, P4.y = 400, P4.z = 200;
	P5.x = 500, P5.y = 400, P5.z = 0;
	P6.x = 300, P6.y = 500, P6.z = 0;
	P7.x = 400, P7.y = 500, P7.z = 0;
	P8.x = 500, P8.y = 500, P8.z = 0;

	if (data->win_ptr == NULL)
		return (1);

    color = ft_create_trgb(0,255,0,0);
    color = ft_get_opposite(color);
    color = ft_add_shade(0.5,color);
    // i = 100;
    // while(i<200)
    // {
    //     j = 100;
    //     while(j<200)
    //     {
    //         ft_pixel_put(&data->img, i, j, color);
    //         j++;
    //     }
    //     i++;
    // }
	ft_iso_projection(&P0.x, &P0.y, P0.z);
	ft_iso_projection(&P1.x, &P1.y, P1.z);
	ft_iso_projection(&P2.x, &P2.y, P2.z);
	ft_iso_projection(&P3.x, &P3.y, P3.z);
	ft_iso_projection(&P4.x, &P4.y, P4.z);
	ft_iso_projection(&P5.x, &P5.y, P5.z);
	ft_iso_projection(&P6.x, &P6.y, P6.z);
	ft_iso_projection(&P7.x, &P7.y, P7.z);
	ft_iso_projection(&P8.x, &P8.y, P8.z);

	ft_draw_line(data, P0, P1, color);
	ft_draw_line(data, P1, P2, color);
	ft_draw_line(data, P0, P3, color);
	ft_draw_line(data, P3, P4, color);
	ft_draw_line(data, P1, P4, color);
	ft_draw_line(data, P4, P5, color);
	ft_draw_line(data, P2, P5, color);
	ft_draw_line(data, P3, P6, color);
	ft_draw_line(data, P4, P7, color);
	ft_draw_line(data, P5, P8, color);
	ft_draw_line(data, P6, P7, color);
	ft_draw_line(data, P7, P8, color);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
    mlx_hook(data.win_ptr, 17, 0L, close, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}

