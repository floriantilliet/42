#include "graphics.h"

#include "stdio.h"

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_data	img;
    int i;
    int j;
    int color;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(mlx, 1920, 1080);
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
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}