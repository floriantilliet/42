/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:20:08 by florian           #+#    #+#             */
/*   Updated: 2024/01/06 15:55:07 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

char	**fd_to_tab(int fd)
{
	char	*line;
	char	*str;
	char	*temp;
	char	**tab;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	line = get_next_line(fd);
	if (!line)
	{
		return (NULL);
	}
	while (line)
	{
		temp = str;
		str = ft_strjoin(str, line);
		free(line);
		if (!str)
			return (free(str), free(line), NULL);
		line = get_next_line(fd);
		free(temp);
	}
	tab = ft_split(str, '\n');
	if (!tab)
		return (free(str), free(line), NULL);
	return (free(str), free(line), tab);
}

char	***tab_to_tabs(char **tab)
{
	char	***tabs;
	int		i;

	i = 0;
	while (tab[i])
		i++;
	tabs = malloc(sizeof(char **) * (i + 1));
	if (!tabs)
		return (NULL);
	i = 0;
	while (tab[i])
	{
		tabs[i] = ft_split(tab[i], ' ');
		if (!tabs[i])
			return (free(tabs), NULL);
		free(tab[i]);
		i++;
	}
	tabs[i] = NULL;
	return (free(tab), tabs);
}

t_point	**tabs_to_map(char ***tabs)
{
	t_point	**map;
	int		i;
	int		j;

	i = 0;
	while (tabs[i])
		i++;
	map = malloc(sizeof(t_point *) * (i + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (tabs[i])
	{
		j = 0;
		while (tabs[i][j])
			j++;
		map[i] = malloc(sizeof(t_point) * (j + 1));
		if (!map[i])
			return (free(map), NULL);
		j = 0;
		while (tabs[i][j])
		{
			map[i][j].x = i;
			map[i][j].y = j;
			map[i][j].z = ft_atoi(tabs[i][j]);
			free(tabs[i][j]);
			j++;
		}
		free(tabs[i]);
		map[i][j].x = -1;
		i++;
	}
	map[i] = NULL;
	return (free(tabs), map);
}

void	get_limits(t_data *data)
{
	int	i;
	int	j;

	data->width = 0;
	data->height = 0;
	data->floor = 0;
	data->ceiling = 0;
	i = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j].x != -1)
		{
			if (data->map[i][j].x > data->width)
				data->width = data->map[i][j].x;
			if (data->map[i][j].y > data->height)
				data->height = data->map[i][j].y;
			if (data->map[i][j].z < data->floor)
				data->floor = data->map[i][j].z;
			if (data->map[i][j].z > data->ceiling)
				data->ceiling = data->map[i][j].z;
			j++;
		}
		i++;
	}
	data->width += 1;
	data->height += 1;
	data->floor *= 10;
	data->ceiling *= 10;
}

// int main(int ac, char **av)
// {
//     int fd;
//     char **tab;
//     char ***tabs;
//     t_point **map;

//     printf("salut");
//     if (ac != 2)
//         return (0);
//     fd = open(av[1], O_RDONLY);
//     if (fd == -1)
//         return (0);
//     tab = fd_to_tab(fd);
//     if (!tab)
//         return (0);
//     tabs = tab_to_tabs(tab);
//     if (!tabs)
//         return (0);
//     map = tabs_to_map(tabs);
//     if (!map)
//         return (0);
//     //print the coordinates of each point of the map
//     int i = 0;
//     int j;
//     while (map[i])
//     {
//         j = 0;
//         while (map[i][j].x != -1)
//         {
//             printf("x: %f, y: %f, z: %f\n", map[i][j].x, map[i][j].y,
// map[i][j].z);
//             j++;
//         }
//         i++;
//     }

//     return (0);
// }