#include "graphics.h"

void	iso_projection(int *x, int *y, int z)
{
	double angle_x_rad = atan(1.0 / sqrt(2.0)); // Calcul de l'angle en radians
	double cos_angle_x = cos(angle_x_rad);
	double sin_angle_x = sin(angle_x_rad);

	// Cosinus et sinus de 45 degrés
	double cos_angle_y = sqrt(2.0) / 2.0;
	double sin_angle_y = sqrt(2.0) / 2.0;

	int previous_x = *x;
	int previous_y = *y;

	// Rotation autour de l'axe Y
	*x = (int)(previous_x * cos_angle_y - z * sin_angle_y);
	z = (int)(previous_x * sin_angle_y + z * cos_angle_y);

	// Rotation autour de l'axe X
	*y = (int)(previous_y * cos_angle_x - z * sin_angle_x);
}