#include <stdio.h>
#include "graphics.h"

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

	P0.x = 860, P0.y = 440, P0.z = 0;
	P1.x = 960, P1.y = 440, P1.z = 0;
	P2.x = 1060, P2.y = 440, P2.z = 0;
	P3.x = 860, P3.y = 540, P3.z = 0;
	P4.x = 960, P4.y = 540, P4.z = 200;
	P5.x = 1060, P5.y = 540, P5.z = 0;
	P6.x = 860, P6.y = 640, P6.z = 0;
	P7.x = 960, P7.y = 640, P7.z = 0;
	P8.x = 1060, P8.y = 640, P8.z = 0;

	if (data->win_ptr == NULL)
		return (1);

    color = ft_create_trgb(0,255,0,0);
    color = ft_get_opposite(color);
    color = ft_add_shade(0.5,color);

	ft_iso_projection(&P0);
	ft_iso_projection(&P1);
	ft_iso_projection(&P2);
	ft_iso_projection(&P3);
	ft_iso_projection(&P4);
	ft_iso_projection(&P5);
	ft_iso_projection(&P6);
	ft_iso_projection(&P7);
	ft_iso_projection(&P8);

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

	data->points[0] = P0;
	data->points[1] = P1; 
	data->points[2] = P2; 
	data->points[3] = P3; 
	data->points[4] = P4; 
	data->points[5] = P5; 
	data->points[6] = P6; 
	data->points[7] = P7; 
	data->points[8] = P8; 
	return (0);
}

int	key_hook(int keycode, t_data *data)
{
	int color;
	const int move_step = 10; // Tu peux ajuster la distance de déplacement

	if (keycode == XK_Up) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
		// Déplace l'image vers le haut
		for (int i = 0; i < 9; i++)
			data->points[i].y -= move_step;
	}
	
	else if (keycode == XK_Down) // Remplace KEY_DOWN par la valeur correspondant à la touche souhaitée
	{
		// Déplace l'image vers le bas
		for (int i = 0; i < 9; i++)
			data->points[i].y += move_step;
	}

	if (keycode == XK_Left) // Remplace KEY_UP par la valeur correspondant à la touche souhaitée
	{
		// Déplace l'image vers le haut
		for (int i = 0; i < 9; i++)
			data->points[i].x -= move_step;
	}

	if (keycode == XK_Right)
	{
		// Déplace l'image vers le haut
		for (int i = 0; i < 9; i++)
			data->points[i].x += move_step;
	}

	if (keycode == XK_d)
	{
    	for (int i = 0; i < 9; i++)
    	{
        	ft_multiply_vector_by_matrix(&data->points[i], ft_get_rot_matrix(-0.01, 'y'));
    	}
	}

	if (keycode == XK_a)
	{
    	for (int i = 0; i < 9; i++)
		{
			ft_multiply_vector_by_matrix(&data->points[i], ft_get_rot_matrix(0.01, 'y'));
		}
	}

	if (data->img.mlx_img) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); // Libère l'image précédente
    }
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT); // Crée une nouvelle image

	color = ft_create_trgb(0,255,0,0);
	ft_draw_line(data, data->points[0], data->points[1], color);
	ft_draw_line(data, data->points[1], data->points[2], color);
	ft_draw_line(data, data->points[0], data->points[3], color);
	ft_draw_line(data, data->points[3], data->points[4], color);
	ft_draw_line(data, data->points[1], data->points[4], color);
	ft_draw_line(data, data->points[4], data->points[5], color);
	ft_draw_line(data, data->points[2], data->points[5], color);
	ft_draw_line(data, data->points[3], data->points[6], color);
	ft_draw_line(data, data->points[4], data->points[7], color);
	ft_draw_line(data, data->points[5], data->points[8], color);
	ft_draw_line(data, data->points[6], data->points[7], color);
	ft_draw_line(data, data->points[7], data->points[8], color);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);; // Redessine l'image avec les nouvelles positions
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

	// mlx_loop_hook(data.mlx_ptr, &render, &data);

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

	P0.x = 860, P0.y = 440, P0.z = 0;
	P1.x = 960, P1.y = 440, P1.z = 0;
	P2.x = 1060, P2.y = 440, P2.z = 0;
	P3.x = 860, P3.y = 540, P3.z = 0;
	P4.x = 960, P4.y = 540, P4.z = 200;
	P5.x = 1060, P5.y = 540, P5.z = 0;
	P6.x = 860, P6.y = 640, P6.z = 0;
	P7.x = 960, P7.y = 640, P7.z = 0;
	P8.x = 1060, P8.y = 640, P8.z = 0;

    color = ft_create_trgb(0,255,0,0);
    color = ft_get_opposite(color);
    color = ft_add_shade(0.5,color);

	ft_iso_projection(&P0);
	ft_iso_projection(&P1);
	ft_iso_projection(&P2);
	ft_iso_projection(&P3);
	ft_iso_projection(&P4);
	ft_iso_projection(&P5);
	ft_iso_projection(&P6);
	ft_iso_projection(&P7);
	ft_iso_projection(&P8);

	ft_draw_line(&data, P0, P1, color);
	ft_draw_line(&data, P1, P2, color);
	ft_draw_line(&data, P0, P3, color);
	ft_draw_line(&data, P3, P4, color);
	ft_draw_line(&data, P1, P4, color);
	ft_draw_line(&data, P4, P5, color);
	ft_draw_line(&data, P2, P5, color);
	ft_draw_line(&data, P3, P6, color);
	ft_draw_line(&data, P4, P7, color);
	ft_draw_line(&data, P5, P8, color);
	ft_draw_line(&data, P6, P7, color);
	ft_draw_line(&data, P7, P8, color);
	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	data.points[0] = P0;
	data.points[1] = P1; 
	data.points[2] = P2; 
	data.points[3] = P3; 
	data.points[4] = P4; 
	data.points[5] = P5; 
	data.points[6] = P6; 
	data.points[7] = P7; 
	data.points[8] = P8; 

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
    mlx_hook(data.win_ptr, 17, 0L, close, &data);
	mlx_key_hook(data.win_ptr, key_hook, &data);

	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}