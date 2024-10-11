/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 12:07:16 by florian           #+#    #+#             */
/*   Updated: 2024/10/11 14:19:19 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include.h"

int mat_equal(t_4matrix a, t_4matrix b)
{
    int i;
    int j;

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

t_4matrix mat_product(t_4matrix a, t_4matrix b)
{
    t_4matrix res;
    int i;
    int j;
    int k;

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

t_tuple mat_tuple_product(t_4matrix a, t_tuple b)
{
    t_tuple res;
    int i;
    int j;

    i = 0;
    res.x = 0;
    res.y = 0;
    res.z = 0;
    res.w = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            res.x += a.mat[i][j] * b.x;
            res.y += a.mat[i][j] * b.y;
            res.z += a.mat[i][j] * b.z;
            res.w += a.mat[i][j] * b.w;
            j++;
        }
        i++;
    }
    return (res);
}

t_4matrix mat_transpose(t_4matrix a)
{
    t_4matrix res;
    int i;
    int j;

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

t_3matrix sub4matrix(t_4matrix a, int row, int col)
{
    t_3matrix res;
    int i;
    int j;
    int sub_i;
    int sub_j;

    sub_i = 0;
    i = 0;
    while (i < 4)
    {
        if (i == row)
        {
            i++;
            continue;
        }
        sub_j = 0;
        j = 0;
        while (j < 4)
        {
            if (j == col)
            {
                j++;
                continue;
            }
            res.mat[sub_i][sub_j] = a.mat[i][j];
            sub_j++;
            j++;
        }
        sub_i++;
        i++;
    }
    return res;
}

t_2matrix sub3matrix(t_3matrix a, int row, int col)
{
    t_2matrix res;
    int i;
    int j;
    int sub_i;
    int sub_j;

    sub_i = 0;
    i = 0;
    while (i < 3)
    {
        if (i == row)
        {
            i++;
            continue;
        }
        sub_j = 0;
        j = 0;
        while (j < 3)
        {
            if (j == col)
            {
                j++;
                continue;
            }
            res.mat[sub_i][sub_j] = a.mat[i][j];
            sub_j++;
            j++;
        }
        sub_i++;
        i++;
    }
    return res;
}

float determinant2(t_2matrix a)
{
    return(a.mat[0][0] * a.mat[1][1] - a.mat[0][1] * a.mat[1][0]);     
}

float determinant3(t_3matrix a)
{
    float res;
    
    res = 0;
    res += a.mat[0][0] * determinant2(sub3matrix(a, 0, 0));
    res -= a.mat[0][1] * determinant2(sub3matrix(a, 0, 1));
    res += a.mat[0][2] * determinant2(sub3matrix(a, 0, 2));
    return (res);       
}


float determinant4(t_4matrix a)
{
    float res;
    
    res = 0;
    res += a.mat[0][0] * determinant3(sub4matrix(a, 0, 0));
    res -= a.mat[0][1] * determinant3(sub4matrix(a, 0, 1));
    res += a.mat[0][2] * determinant3(sub4matrix(a, 0, 2));
    res -= a.mat[0][3] * determinant3(sub4matrix(a, 0, 3));
    return (res);
}

t_4matrix inverse4(t_4matrix a)
{
    t_4matrix res;
    int i;
    int j;
    float det;

    det = determinant4(a);
    i = 0;
    while (i < 4)
    {
        j = 0;
        while (j < 4)
        {
            res.mat[i][j] = determinant3(sub4matrix(a, i, j))/det;
            if ((i + j) % 2 == 1)
                res.mat[i][j] *= -1;
            j++;
        }
        i++;
    }
    return (mat_transpose(res));
}