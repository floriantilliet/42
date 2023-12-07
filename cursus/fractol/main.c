#include "graphics.h"

#include "stdio.h"

#define KEY_ESC 53

int close(t_data *img)
{
    mlx_destroy_image(img->mlx, img->img);
    mlx_destroy_window(img->mlx, img->win);
    exit(1);
    return (0);
}

int key_hook(int key_code, t_data *img)
{
    printf("%d\n", key_code);
    if (key_code == XK_Escape)
        close(img);
    return (0);
}
int	main(void)
{
	t_data	img;
    int i;
    int j;
    int color;

    
	img.mlx = mlx_init();
	img.win = mlx_new_window(img.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(img.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
    color = create_trgb(0,127,141,150);
    color = get_opposite(color);
    color = add_shade(0.5,color);
    printf("%d", color);
    i = 250;
    while(i<500)
    {
        j = 250;
        while(j<500)
        {
            my_mlx_pixel_put(&img, i, j, color);
            j++;
        }
        i++;
    }
    mlx_key_hook(img.win, key_hook, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_hook(img.win, 17, 0L, close, &img);
	mlx_loop(img.mlx);
}
