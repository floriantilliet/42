/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   include.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 09:53:46 by florian           #+#    #+#             */
/*   Updated: 2024/10/11 11:00:09 by florian          ###   ########.fr       */
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

#endif