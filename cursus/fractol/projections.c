#include "graphics.h"

double	rad(double deg)
{
	return (deg * M_PI / 180);
}

typedef struct s_matrix
{
	t_point	i;
	t_point	j;
	t_point	k;
}	t_matrix;

void ft_multiply_vector_by_matrix(t_point *v, t_matrix m)
{
    // Utiliser des variables temporaires de type float ou double
    double temp_x, temp_y, temp_z;

    temp_x = v->x * m.i.x + v->y * m.i.y + v->z * m.i.z;
    temp_y = v->x * m.j.x + v->y * m.j.y + v->z * m.j.z;
    temp_z = v->x * m.k.x + v->y * m.k.y + v->z * m.k.z;

    // Convertir les résultats en int avant de les assigner
    v->x = (int)round(temp_x);
    v->y = (int)round(temp_y);
    v->z = (int)round(temp_z);
}

t_matrix	ft_get_rot_matrix(double deg, char axis)
{
	if (axis == 'x')
		return ((t_matrix){
			(t_point){1, 0, 0},
			(t_point){0, cos(deg), -sin(deg)},
			(t_point){0, sin(deg), cos(deg)}
	});
	if (axis == 'y')
		return ((t_matrix){
			(t_point){cos(deg), 0, -sin(deg)},
			(t_point){0, 1, 0},
			(t_point){sin(deg), 0, cos(deg)}
	});
	if (axis == 'z')
		return ((t_matrix){
			(t_point){cos(rad(deg)), -sin(rad(deg)), 0},
			(t_point){sin(rad(deg)), cos(rad(deg)), 0},
			(t_point){0, 0, 1}
	});
	return ((t_matrix){
		(t_point){1, 0, 0},
		(t_point){0, 1, 0},
		(t_point){0, 0, 1}
	});
}

#include <stdio.h>

void ft_iso_projection(t_point *point)
{
    double z_deg = 45;
    double x_deg = rad(atan(sqrt(2)));

	printf("Avant transformation: %d %d %d\n", point->x, point->y, point->z);

    // Rotation autour de l'axe Z
    ft_multiply_vector_by_matrix(point, ft_get_rot_matrix(z_deg, 'z'));

    // Rotation autour de l'axe X
    ft_multiply_vector_by_matrix(point, ft_get_rot_matrix(x_deg, 'x'));

    // Projection isométrique
    // Exemple de projection simple :
    int temp_x = point->x;
    int temp_y = point->y;
    point->x = (temp_x - temp_y) * sqrt(2) / 2;
    point->y = (temp_x + temp_y) * sqrt(2) / 2 - point->z;

	printf("Après transformation: %d %d %d\n", point->x, point->y, point->z);
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
