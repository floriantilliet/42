/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: florian <florian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 18:31:07 by florian           #+#    #+#             */
/*   Updated: 2024/01/09 15:49:08 by florian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"

t_point	create_point_from_tab(char **tab, int i, int j)
{
	t_point	point;

	point.x = i;
	point.y = j;
	point.z = ft_atoi(tab[j]);
	return (point);
}

t_point	*allocate_and_init_line(char **tab_line, int i)
{
	t_point	*line;
	int		j;

	j = 0;
	while (tab_line[j])
		j++;
	line = malloc(sizeof(t_point) * (j + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (tab_line[j])
	{
		line[j] = create_point_from_tab(tab_line, i, j);
		j++;
	}
	line[j].x = -1;
	return (line);
}

void	free_tab(char **tab)
{
	int	j;

	j = 0;
	if (!tab)
		return ;
	while (tab[j])
	{
		free(tab[j]);
		j++;
	}
	free(tab);
}

void	free_tabs(char ***tabs)
{
	int	i;

	i = 0;
	if (!tabs)
		return ;
	while (tabs[i])
	{
		free_tab(tabs[i]);
		i++;
	}
	free(tabs);
}

void	free_map(t_point **map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}
