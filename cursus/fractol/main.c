#include "graphics.h"

#include "stdio.h"
#include <time.h>

#define KEY_ESC 53

int close(t_data *img)
{
    mlx_destroy_image(img->mlx, img->img);
    mlx_destroy_window(img->mlx, img->win);
    exit(1);
    return (0);
}

int key_press_hook(int key_code, t_data *img)
{
    img->key_pressed = 1;
    img->start = time(NULL);
    if (key_code == XK_Escape)
        close(img);
    return (0);
}

int key_release_hook(int key_code, t_data *img)
{
    if (img->key_pressed)
    {
        time_t end_time;
        end_time = time(NULL);
        double duration;
        duration = difftime(end_time, img->start);
        printf("%f", duration);
        if (duration >= 3.0)
            printf("Key held down for more than 3 seconds.\n");
        img->key_pressed = 0;
    }
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
    mlx_hook(img.win, 2, 1L<<0, key_press_hook, &img);
    mlx_hook(img.win, 3, 1L<<1, key_release_hook, &img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
    mlx_hook(img.win, 17, 0L, close, &img);
	mlx_loop(img.mlx);
}
