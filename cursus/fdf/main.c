/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:20:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:14:41 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	main(int ac, char **av)
{

	if (ac != 2)
        return (0);

	t_data	data;
	ft_init_image(&data);
	ft_parsing(&data, av[1]);
	
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &key_hook, &data);
	mlx_hook(data.win_ptr, 17, 0L, close_image, &data);
	mlx_hook(data.win_ptr, 4, 1L<<2, ft_mouse_down, &data);
	mlx_hook(data.win_ptr, 5, 1L<<3, ft_mouse_up, &data);
	mlx_hook(data.win_ptr, 6, 1L<<6, ft_mouse_move, &data);
    mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_loop(data.mlx_ptr);
}