/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   square_finder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 11:17:21 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/27 11:17:23 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"

int	get_min(int left, int diagonal, int up)
{
	int	min;

	min = left;
	if (diagonal < min)
		min = diagonal;
	if (up < min)
		min = up;
	return (min);
}

int	**solve(int **input_tab, int line_len, int col_len)
{
	int	i;
	int	j;

	i = 1;
	while (i < col_len)
	{
		j = 1;
		while (j < line_len)
		{
			if (input_tab[i][j] != 0)
			{
				input_tab[i][j] = get_min(input_tab[i][j - 1], input_tab[i
						- 1][j - 1], input_tab[i - 1][j]) + 1;
			}
			j++;
		}
		i++;
	}
	return (input_tab);
}

struct s_coord	get_bsq(int **map, int line_len, int col_len)
{
	int		i;
	int		j;
	t_coord	coord;

	i = 0;
	coord.x = 0;
	coord.y = 0;
	coord.max = 0;
	while (i < col_len)
	{
		j = 0;
		while (j < line_len)
		{
			if (map[i][j] > coord.max)
			{
				coord.max = map[i][j];
				coord.y = i;
				coord.x = j;
			}
			j++;
		}
		i++;
	}
	return (coord);
}

char	*bsq(char *str, t_coord coord, char *charset, int line_len)
{
	int	i;
	int	j;
	int	k;

	i = coord.max;
	k = skip_fline(str) + 1 + (coord.x - coord.max + 1) + (coord.y * line_len)
		+ coord.y;
	while (i > 0)
	{
		j = 0;
		while (j < coord.max)
		{
			str[k] = charset[2];
			j++;
			k++;
		}
		i--;
		coord.y--;
		k = skip_fline(str) + 1 + (coord.x - coord.max + 1) + (coord.y
				* line_len) + coord.y;
	}
	return (str);
}

void	get_and_solve(char *str)
{
	int		line_len;
	int		col_len;
	int		**tab;
	t_coord	coord;

	col_len = check_line2(str, take_sep(str));
	line_len = ft_linelen(str + check_first_line(str) + 1);
	tab = def_matrix(line_len, col_len);
	tab = get_matrix(tab, str, take_sep(str), line_len);
	tab = solve(tab, line_len, col_len);
	coord = get_bsq(tab, line_len, col_len);
	str = bsq(str, coord, take_sep(str), line_len);
	ft_putstr2((str + 1 + check_first_line(str)), line_len, col_len);
	free_matrix(tab, col_len);
	free(str);
}

/* int main()
{
	char *str = "map_example2";

	str = get_and_solve(str);
	printf("%s\n", str);
}   */
