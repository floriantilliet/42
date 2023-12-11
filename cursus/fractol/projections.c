#include "graphics.h"

// void	iso_projection(int *x, int *y, int z)
// {
// 	double	cos_angle_x;
// 	double	sin_angle_x;
// 	double	cos_angle_y;
// 	double	sin_angle_y;
// 	int		previous_x;
// 	int		previous_y;

// 	double angle_x_rad = atan(1.0 / sqrt(2.0)); // Calcul de l'angle en radians
// 	cos_angle_x = cos(angle_x_rad);
// 	sin_angle_x = sin(angle_x_rad);
// 	// cosinus et sinus de 45 degrés
// 	cos_angle_y = sqrt(2.0) / 2.0;
// 	sin_angle_y = sqrt(2.0) / 2.0;
// 	previous_x = *x;
// 	previous_y = *y;
// 	// Rotation autour de l'axe Y
// 	*x = (int)(previous_x * cos_angle_y - z * sin_angle_y);
// 	z = (int)(previous_x * sin_angle_y + z * cos_angle_y);
// 	// Rotation autour de l'axe X
// 	*y = (int)(previous_y * cos_angle_x - z * sin_angle_x);
// }

void	draw_line(t_data *data, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	if (x0 < x1)
		sx = 1;
	else
		sx = -1;
	dy = -abs(y1 - y0);
	if (y0 < y1)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		ft_pixel_put(&data->img, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}
