/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/18 15:20:50 by florian           #+#    #+#             */
/*   Updated: 2024/01/08 16:46:36 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "graphics.h"

int close_image(t_data *data)
{
    mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	mlx_destroy_image(data->mlx_ptr, data->img.mlx_img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);

	int x;
	x = 0;
	while (x<data->width)
	{
		free(data->map[x]);
		x++;
	}
	free(data->map);
	exit(0);
    return (0);
}

int	render(t_data *data)
{   
    t_data  proj;
	int x;
	
	if (data->win_ptr == NULL)
		return (1);

	if (data->img.mlx_img) {
        mlx_destroy_image(data->mlx_ptr, data->img.mlx_img); // Libère l'image précédente
    }
    data->img.mlx_img = mlx_new_image(data->mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);

    proj = ft_iso_projection(data);

    ft_draw(data, proj);

	x = 0;
	while (x<data->width)
	{
		free(proj.map[x]);
		x++;
	}
	free(proj.map);

	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	main(int ac, char **av)
{

	if (ac != 2)
        return (0);

	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	data.win_ptr = mlx_new_window(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WINDOW_WIDTH, WINDOW_HEIGHT);
	
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	int fd;
    char **tab;
    char ***tabs;

    fd = open(av[1], O_RDONLY);
    if (fd == -1)
        return (0);
    tab = fd_to_tab(fd);
    if (!tab)
        return (0);
    tabs = tab_to_tabs(tab);
    if (!tabs)
        return (0);
    data.map = tabs_to_map(tabs);
    if (!data.map)
	{
        return (0);
	}
	get_limits(&data);
	data.mouse_button = 0;
	data.angle_x = 0;
	data.angle_y = 0;
	data.angle_z = 0;
	data.offset_x = 0;
	data.offset_y = 0;
	
	// mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, data.img.mlx_img, 0, 0);

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &key_hook, &data);
	mlx_hook(data.win_ptr, 17, 0L, close_image, &data);
	mlx_hook(data.win_ptr, 4, 1L<<2, ft_mouse_down, &data);
	mlx_hook(data.win_ptr, 5, 1L<<3, ft_mouse_up, &data);
	mlx_hook(data.win_ptr, 6, 1L<<6, ft_mouse_move, &data);
    mlx_loop_hook(data.mlx_ptr, &render, &data);

	mlx_loop(data.mlx_ptr);
}