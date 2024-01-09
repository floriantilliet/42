/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:20:08 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:50:38 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

char	*read_file_into_str(int fd)
{
	char	*line;
	char	*str;
	char	*temp;

	str = ft_strdup("");
	if (!str)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		temp = str;
		str = ft_strjoin(str, line);
		free(line);
		if (!str)
			return (free(str), NULL);
		line = get_next_line(fd);
		free(temp);
	}
	return (str);
}

char	**fd_to_tab(int fd)
{
	char	*str;
	char	**tab;

	str = read_file_into_str(fd);
	if (!str)
		return (NULL);
	tab = ft_split(str, '\n');
	free(str);
	return (tab);
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

	i = 0;
	while (tabs && tabs[i])
		i++;
	map = malloc(sizeof(t_point *) * (i + 1));
	if (!map)
		return (NULL);
	i = 0;
	while (tabs[i])
	{
		map[i] = allocate_and_init_line(tabs[i], i);
		if (!map[i])
			return (free_map(map), NULL);
		free_tab(tabs[i]);
		i++;
	}
	map[i] = NULL;
	free(tabs);
	return (map);
}

int	ft_get_map(t_data *data, char *path)
{
	int		fd;
	char	**tab;
	char	***tabs;

	fd = open(path, O_RDONLY);
	if (fd == -1)
		return (0);
	tab = fd_to_tab(fd);
	if (!tab)
		return (0);
	tabs = tab_to_tabs(tab);
	if (!tabs)
		return (0);
	data->map = tabs_to_map(tabs);
	if (!data->map)
		return (0);
	get_limits(data);
	init_shifts(data);
	return (1);
}
