#include "graphics.h"

#include <stdio.h>

double	rad(double deg)
{
	return (deg * M_PI / 180);
}

t_point ft_multiply_vector_by_matrix(t_point *v, t_matrix m)
{
	t_point res;
    // Utiliser des variables temporaires de type float ou double
    double temp_x, temp_y, temp_z;

	// normalize the vectors before multiplying them
	// double length = sqrt(m.i.x * m.i.x + m.i.y * m.i.y + m.i.z * m.i.z);
	// m.i.x /= length;
	// m.i.y /= length;
	// m.i.z /= length;

	// length = sqrt(m.j.x * m.j.x + m.j.y * m.j.y + m.j.z * m.j.z);
	// m.j.x /= length;
	// m.j.y /= length;
	// m.j.z /= length;

	// length = sqrt(m.k.x * m.k.x + m.k.y * m.k.y + m.k.z * m.k.z);
	// m.k.x /= length;
	// m.k.y /= length;
	// m.k.z /= length;

    temp_x = v->x * m.i.x + v->y * m.i.y + v->z * m.i.z;
    temp_y = v->x * m.j.x + v->y * m.j.y + v->z * m.j.z;
    temp_z = v->x * m.k.x + v->y * m.k.y + v->z * m.k.z;

    // Convertir les résultats en int avant de les assigner
    res.x = (int)(temp_x);
    res.y = (int)(temp_y);
    res.z = (int)(temp_z);

	return(res);
}

t_matrix	ft_get_rot_matrix(double deg, char axis)
{
	if (axis == 'x')
		return ((t_matrix){
			(t_point){1., 0., 0.},
			(t_point){0., cos(deg), -sin(deg)},
			(t_point){0., sin(deg), cos(deg)}
	});
	if (axis == 'y')
		return ((t_matrix){
			(t_point){cos(deg), 0., -sin(deg)},
			(t_point){0., 1., 0.},
			(t_point){sin(deg), 0., cos(deg)}
	});
	if (axis == 'z')
		return ((t_matrix){
			(t_point){cos(rad(deg)), -sin(rad(deg)), 0.},
			(t_point){sin(rad(deg)), cos(rad(deg)), 0.},
			(t_point){0., 0., 1.}
	});
	return ((t_matrix){
		(t_point){1., 0., 0.},
		(t_point){0., 1., 0.},
		(t_point){0., 0., 1.},
	});
}

t_data ft_iso_projection(t_data *data)
{	
    t_data proj;

    // Calculer le centre de la fenêtre de rendu
    int window_center_x = WINDOW_WIDTH / 2;
    int window_center_y = WINDOW_HEIGHT / 2;

    double z_deg = 45;
    double x_deg = atan(sqrt(2)) + data->angle_x;
	double y_deg = data->angle_y;

	for (int i = 0; i < NB_POINTS; i++)
	{
    // Rotation autour de l'axe Z
    proj.points[i] = ft_multiply_vector_by_matrix(&data->points[i], ft_get_rot_matrix(z_deg, 'z'));

    // Rotation autour de l'axe X
    proj.points[i] = ft_multiply_vector_by_matrix(&proj.points[i], ft_get_rot_matrix(x_deg, 'x'));

	//rotation autour de l'axe Y
	proj.points[i] = ft_multiply_vector_by_matrix(&proj.points[i], ft_get_rot_matrix(y_deg, 'y'));

	proj.points[i].x += window_center_x;
    proj.points[i].y += window_center_y;
	}

	// proj = *data;
	return(proj);
}

void	ft_draw_line(t_data *data, t_point P0, t_point P1, int color)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;

	dx = fabs(P0.x - P1.x);
	if (P0.x < P1.x)
		sx = 1;
	else
		sx = -1;
	dy = -fabs(P1.y - P0.y);
	if (P0.y < P1.y)
		sy = 1;
	else
		sy = -1;
	err = dx + dy;
	while (1)
	{
		ft_pixel_grad(&data->img, P0.x, P0.y, P0.z, color);
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

void ft_draw_image(t_data *data, t_data proj, int color)
{
    for (int i = 0; i < NB_POINTS - 1; i++)
    {
        ft_draw_line(data, proj.points[i], proj.points[i + 1], color);
    }
    // Dessiner la dernière ligne entre le dernier point et le premier point pour fermer la forme
    ft_draw_line(data, proj.points[NB_POINTS - 1], proj.points[0], color);
}

void draw_lines_recursive(t_data *data,t_data proj, int start, int end, int color) {
    // Condition de sortie de la récursion
    if (start >= end) {
        return;
    }
	
    // Dessiner un trait entre les points start et end
    ft_draw_line(data, proj.points[start], proj.points[end], color);

    // Appel récursif pour les sous-ensembles de points
    int mid = (start + end) / 2;
    draw_lines_recursive(data, proj, start, mid, color);
    draw_lines_recursive(data, proj, mid + 1, end, color);
}