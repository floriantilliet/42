/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:53:46 by florian           #+#    #+#             */
/*   Updated: 2024/10/11 14:18:33 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHICS_H
# define GRAPHICS_H

# include "get_next_line/get_next_line_bonus.h"
# include "libft/libft.h"
# include "mlx/mlx.h"
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

# define EPSILON 0.00001
# define WINDOW_WIDTH 1280
# define WINDOW_HEIGHT 1024

typedef struct s_tuple
{
	double		x;
    double		y;
    double		z;
    int		w;
}				t_tuple;

typedef struct		s_4matrix{
	double			mat[4][4];
}					t_4matrix;

typedef struct		s_3matrix{
	double			mat[3][3];
}					t_3matrix;

typedef struct		s_2matrix{
	double			mat[2][2];
}					t_2matrix;

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_img;

typedef struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_data;

int	ft_init_image(t_data *data);
int	close_image(t_data *data);
int mat_equal(t_4matrix a, t_4matrix b);
t_4matrix mat_product(t_4matrix a, t_4matrix b);
t_tuple mat_tuple_product(t_4matrix a, t_tuple b);
t_3matrix sub4matrix(t_4matrix a, int row, int col);
t_2matrix sub3matrix(t_3matrix a, int row, int col);
float determinant2(t_2matrix a);
float determinant3(t_3matrix a);
float determinant4(t_4matrix a);
t_4matrix inverse4(t_4matrix a);

#endif