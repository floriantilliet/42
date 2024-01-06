#include "graphics.h"

#include <stdio.h>

double rad(double deg)
{
    return deg * DEG_TO_RAD;
}

t_point ft_multiply_vector_by_matrix(t_point *v, t_matrix m)
{
	t_point res;

    res.x = v->x * m.i.x + v->y * m.i.y + v->z * m.i.z;
    res.y = v->x * m.j.x + v->y * m.j.y + v->z * m.j.z;
    res.z = v->x * m.k.x + v->y * m.k.y + v->z * m.k.z;

	return(res);
}

t_matrix	ft_get_rot_matrix(double deg, char axis)
{
	if (axis == 'x')
		return ((t_matrix){
			(t_point){1., 0., 0.},
			(t_point){0., cos(rad(deg)), -sin(rad(deg))},
			(t_point){0., sin(rad(deg)), cos(rad(deg))}
	});
	if (axis == 'y')
		return ((t_matrix){
			(t_point){cos(rad(deg)), 0., -sin(rad(deg))},
			(t_point){0., 1., 0.},
			(t_point){sin(deg), 0., cos(rad(deg))}
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
    double x_deg = atan(sqrt(2)) + 45 + data->angle_x;
    double y_deg = - data->angle_y;

    // Calculer les matrices de rotation une seule fois
    t_matrix rot_z = ft_get_rot_matrix(z_deg, 'z');
    t_matrix rot_x = ft_get_rot_matrix(x_deg, 'x');
    t_matrix rot_y = ft_get_rot_matrix(y_deg, 'y');

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
            proj.map[x][y] = ft_multiply_vector_by_matrix(&data->map[x][y], rot_z);
            proj.map[x][y] = ft_multiply_vector_by_matrix(&proj.map[x][y], rot_x);
            proj.map[x][y] = ft_multiply_vector_by_matrix(&proj.map[x][y], rot_y);
            proj.map[x][y].z = data->map[x][y].z;
            proj.map[x][y].x *= -1;
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
    return(proj);
}
