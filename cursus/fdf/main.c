/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:20:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 16:16:01 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

int	ft_file_name_error(char *file_name)
{
	size_t	file_name_len;

	file_name_len = ft_strlen(file_name);
	if (file_name_len < 4)
		return (0);
	if (ft_strncmp(&file_name[file_name_len - 4], ".fdf", 4))
		return (0);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac != 2)
		return (0);
	if (!ft_file_name_error(av[1]))
		return (0);
	if (!ft_get_map(&data, av[1]))
		return (0);
	if (!ft_init_image(&data))
		return (0);
	ft_loop_hooks(&data);
	return (0);
}
