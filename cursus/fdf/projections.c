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

	int x;
	int y;

    double z_deg = 45 + data->angle_z;
    double x_deg = atan(sqrt(2)) + data->angle_x;
	double y_deg = data->angle_y;

	proj.map = malloc(sizeof(t_point*) * data->width);
	x = 0;
	while (x<data->width)
	{
		proj.map[x] = malloc(sizeof(t_point) * data->height);
		x++;
	}
	

	x = 0;
	while (x < data->width)
	{
		y = 0;
		while (y < data->height)
		{	
			proj.map[x][y] = ft_multiply_vector_by_matrix(&data->map[x][y], ft_get_rot_matrix(z_deg, 'z'));
			proj.map[x][y] = ft_multiply_vector_by_matrix(&proj.map[x][y], ft_get_rot_matrix(x_deg, 'x'));
			proj.map[x][y] = ft_multiply_vector_by_matrix(&proj.map[x][y], ft_get_rot_matrix(y_deg, 'y'));
			proj.map[x][y].z = data->map[x][y].z;
			proj.map[x][y].y += data->offset_y;
			proj.map[x][y].x += data->offset_x;
			proj.map[x][y].x = round(proj.map[x][y].x * data->zoom);
			proj.map[x][y].y = round(proj.map[x][y].y * data->zoom);
			proj.map[x][y].x += window_center_x;
			proj.map[x][y].y += window_center_y;
			y++;
		}
		x++;
	}
	// proj = *data;
	return(proj);
}

double interpolate_altitude(t_point start, t_point end, t_point current) {
    // Calculer les distances entre les points de départ et d'arrivée
    double dx = end.x - start.x;
    double dy = end.y - start.y;
    double dz = end.z - start.z;

    // Calculer la distance horizontale entre le point de départ et le point intermédiaire
    double distance = sqrt((current.x - start.x) * (current.x - start.x) + (current.y - start.y) * (current.y - start.y));

    // Interpoler l'altitude en utilisant la distance horizontale
    double interpolated_z = start.z + (distance / sqrt(dx * dx + dy * dy)) * dz;

    return interpolated_z;
}

void	ft_draw_line(t_data *data, t_point P0, t_point P1)
{
	int	dx;
	int	sx;
	int	dy;
	int	sy;
	int	err;
	int	e2;
	t_point start = P0;
	t_point end = P1;
	t_point current;

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
		current.x = P0.x;
		current.y = P0.y;
		current.z = interpolate_altitude(start, end, current);
		ft_pixel_put(&data->img, P0.x, P0.y, get_altitude_color(current.z));
		// ft_pixel_put(&data->img, P0.x, P0.y, ft_create_trgb(0, 255, 0, 0));
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

void	ft_draw(t_data *data, t_data proj)
{
    int	x;
    int	y;
    x = 0;
    while (x < data->width)
    {
        y = 0;
        while (y < data->height)
        {
            if (x < data->width - 1) // Check if it's not the last column
                ft_draw_line(data, proj.map[x][y], proj.map[x + 1][y]);
            if (y < data->height - 1) // Check if it's not the last row
                ft_draw_line(data, proj.map[x][y], proj.map[x][y + 1]);
            y++;
        }
        x++;
    }
}
