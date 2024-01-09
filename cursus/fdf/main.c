/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:20:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:37:33 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	main(int ac, char **av)
{

	if (ac != 2)
        return (0);

	t_data	data;
	if (!ft_init_image(&data))
		return (0);
	if (!ft_get_map(&data, av[1]))
		return (0);
	ft_loop_hooks(&data);
	return (0);
}