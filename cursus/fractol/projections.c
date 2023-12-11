#include "graphics.h"

void	ft_iso_projection(int *x, int *y, int z)
{
	double	cos_angle_x;
	double	sin_angle_x;
	double	cos_angle_y;
	double	sin_angle_y;
	int		previous_x;
	int		previous_y;

	double angle_x_rad = atan(1.0 / sqrt(2.0)); // Calcul de l'angle en radians
	cos_angle_x = cos(angle_x_rad);
	sin_angle_x = sin(angle_x_rad);
	// cosinus et sinus de 45 degrés
	cos_angle_y = sqrt(2.0) / 2.0;
	sin_angle_y = sqrt(2.0) / 2.0;
	previous_x = *x;
	previous_y = *y;
	// Rotation autour de l'axe Y
	*x = (int)(previous_x * cos_angle_y - z * sin_angle_y);
	z = (int)(previous_x * sin_angle_y + z * cos_angle_y);
	// Rotation autour de l'axe X
	*y = (int)(previous_y * cos_angle_x - z * sin_angle_x);
}

void	ft_draw_line(t_data *data, t_point P0, t_point P1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = abs(P0.x - P1.x);
	if (P0.x < P1.x)
		sx = 1;
	else
		sx = -1;
	dy = -abs(P1.y - P0.y);
	if (P0.y < P1.y)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		ft_pixel_put(&data->img, P0.x, P0.y, color);
		if (P0.x == P1.x && P0.y == P1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			P0.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			P0.y += sy;
		}
	}
}
