/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basefunc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:21:56 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 14:21:58 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"

int	ft_strlen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0')
	{
		count++;
	}
	return (count);
}

int	ft_linelen(char *str)
{
	int	count;

	count = 0;
	while (str[count] != '\0' && str[count] != '\n')
	{
		count++;
	}
	return (count);
}

int	**def_matrix(int line_len, int col_len)
{
	int	**tab;
	int	i;
	int	j;

	i = -1;
	tab = malloc(sizeof(int *) * col_len);
	if (tab == NULL)
		return (NULL);
	while (++i < col_len)
	{
		tab[i] = malloc(sizeof(int) * line_len);
		if (tab[i] == NULL)
			return (NULL);
	}
	i = -1;
	j = -1;
	while (++i < line_len)
		while (++j < line_len)
			tab[i][j] = 0;
	return (tab);
}

void	free_matrix(int **map, int col_len)
{
	int	i;

	i = 0;
	while (i < col_len)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

int	**get_matrix(int **tab, char *str, char *charset, int line_len)
{
	int	i;
	int	line;
	int	col;

	line = 0;
	col = 0;
	i = 0;
	while (str[i] != '\n')
		i++;
	i++;
	while (str[i])
	{
		if (str[i] == '\n')
		{
			i++;
			col = 0;
			line += 1;
		}
		if (str[i] == '\0' || line == line_len)
			return (tab);
		tab[line][col] = get_cell_value(str[i], charset);
		i++;
		col++;
	}
	return (tab);
}
