/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:07:16 by florian           #+#    #+#             */
/*   Updated: 2024/11/11 21:21:30 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int	mat_equal(t_4matrix a, t_4matrix b)
{
	int	i;
	int	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (a.mat[i][j] != b.mat[i][j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

t_4matrix	mat_product(t_4matrix a, t_4matrix b)
{
	t_4matrix	res;
	int			i;
	int			j;
	int			k;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.mat[i][j] = 0;
			k = 0;
			while (k < 4)
			{
				res.mat[i][j] += a.mat[i][k] * b.mat[k][j];
				k++;
			}
			j++;
		}
		i++;
	}
	return (res);
}

t_tuple	mat_tuple_product(t_4matrix a, t_tuple b)
{
	t_tuple	res;

	res.x = a.mat[0][0] * b.x + a.mat[0][1] * b.y + a.mat[0][2] * b.z
		+ a.mat[0][3] * b.w;
	res.y = a.mat[1][0] * b.x + a.mat[1][1] * b.y + a.mat[1][2] * b.z
		+ a.mat[1][3] * b.w;
	res.z = a.mat[2][0] * b.x + a.mat[2][1] * b.y + a.mat[2][2] * b.z
		+ a.mat[2][3] * b.w;
	res.w = a.mat[3][0] * b.x + a.mat[3][1] * b.y + a.mat[3][2] * b.z
		+ a.mat[3][3] * b.w;
	return (res);
}

t_4matrix	mat_transpose(t_4matrix a)
{
	t_4matrix	res;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.mat[i][j] = a.mat[j][i];
			j++;
		}
		i++;
	}
	return (res);
}

t_3matrix	sub4matrix(t_4matrix a, int row, int col)
{
	t_3matrix	res;
	int			i;
	int			j;
	int			sub_i;
	int			sub_j;

	sub_i = 0;
	i = 0;
	while (i < 4)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		sub_j = 0;
		j = 0;
		while (j < 4)
		{
			if (j == col)
			{
				j++;
				continue ;
			}
			res.mat[sub_i][sub_j] = a.mat[i][j];
			sub_j++;
			j++;
		}
		sub_i++;
		i++;
	}
	return (res);
}

t_2matrix	sub3matrix(t_3matrix a, int row, int col)
{
	t_2matrix	res;
	int			i;
	int			j;
	int			sub_i;
	int			sub_j;

	sub_i = 0;
	i = 0;
	while (i < 3)
	{
		if (i == row)
		{
			i++;
			continue ;
		}
		sub_j = 0;
		j = 0;
		while (j < 3)
		{
			if (j == col)
			{
				j++;
				continue ;
			}
			res.mat[sub_i][sub_j] = a.mat[i][j];
			sub_j++;
			j++;
		}
		sub_i++;
		i++;
	}
	return (res);
}

double	determinant2(t_2matrix a)
{
	return (a.mat[0][0] * a.mat[1][1] - a.mat[0][1] * a.mat[1][0]);
}

double	determinant3(t_3matrix a)
{
	double	res;

	res = 0;
	res += a.mat[0][0] * determinant2(sub3matrix(a, 0, 0));
	res -= a.mat[0][1] * determinant2(sub3matrix(a, 0, 1));
	res += a.mat[0][2] * determinant2(sub3matrix(a, 0, 2));
	return (res);
}

double	determinant4(t_4matrix a)
{
	double	res;

	res = 0;
	res += a.mat[0][0] * determinant3(sub4matrix(a, 0, 0));
	res -= a.mat[0][1] * determinant3(sub4matrix(a, 0, 1));
	res += a.mat[0][2] * determinant3(sub4matrix(a, 0, 2));
	res -= a.mat[0][3] * determinant3(sub4matrix(a, 0, 3));
	return (res);
}

t_4matrix	inverse4(t_4matrix a)
{
	t_4matrix	res;
	int			i;
	int			j;
	double		det;

	det = determinant4(a);
	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			res.mat[i][j] = determinant3(sub4matrix(a, i, j)) / det;
			if ((i + j) % 2 == 1)
				res.mat[i][j] *= -1;
			j++;
		}
		i++;
	}
	return (mat_transpose(res));
}

t_4matrix	identity4(void)
{
	t_4matrix	res;
	int			i;
	int			j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (i != j)
				res.mat[i][j] = 0;
			else
				res.mat[i][j] = 1;
			j++;
		}
		i++;
	}
	return (res);
}

t_4matrix	translation_mat(double x, double y, double z)
{
	t_4matrix	res;

	res = identity4();
	res.mat[0][3] = x;
	res.mat[1][3] = y;
	res.mat[2][3] = z;
	return (res);
}

t_4matrix	scaling_mat(double x, double y, double z)
{
	t_4matrix	res;

	res = identity4();
	res.mat[0][0] = x;
	res.mat[1][1] = y;
	res.mat[2][2] = z;
	return (res);
}

t_4matrix	rotation_x_mat(double angle)
{
	t_4matrix	res;

	res = identity4();
	res.mat[1][1] = cos(angle);
	res.mat[1][2] = -sin(angle);
	res.mat[2][1] = sin(angle);
	res.mat[2][2] = cos(angle);
	return (res);
}

t_4matrix	rotation_y_mat(double angle)
{
	t_4matrix res;

	res = identity4();
	res.mat[0][0] = cos(angle);
	res.mat[0][2] = sin(angle);
	res.mat[2][0] = -sin(angle);
	res.mat[2][2] = cos(angle);
	return (res);
}

t_4matrix rotation_z_mat(double angle)
{
    t_4matrix res;

    res = identity4();
    res.mat[0][0] = cos(angle);
    res.mat[0][1] = -sin(angle);
    res.mat[1][0] = sin(angle);
    res.mat[1][1] = cos(angle);
    return (res);
}

t_4matrix shearing_mat(t_shearing_params params)
{
    t_4matrix res;

    res = identity4();
    res.mat[0][1] = params.xy;
    res.mat[0][2] = params.xz;
    res.mat[1][0] = params.yx;
    res.mat[1][2] = params.yz;
    res.mat[2][0] = params.zx;
    res.mat[2][1] = params.zy;
    return (res);
}