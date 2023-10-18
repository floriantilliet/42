/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/16 15:54:26 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/17 21:25:18 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	check_doubles_line(int map[4][4], int col, int num);
int	check_doubles_col(int map[4][4], int line, int num);
int	check_updown(int map[4][4], int col, int ctr[16]);
int	check_downup(int map[4][4], int col, int ctr[16]);
int	check_leftright(int map[4][4], int line, int ctr[16]);
int	check_rightleft(int map[4][4], int line, int ctr[16]);
int	check_ctr(int map[4][4], int line, int col, int ctr[16]);

void	print_puzzle_map(int map[4][4])
{
	int		i;
	int		j;
	char	temp;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			temp = '0' + map[i][j];
			write(1, &temp, 1);
			if (j < 3)
				write (1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
}

int	solve(int map[4][4], int line, int col, int ctr[16])
{
	int	num;

	if (line == 4)
		return (1);
	if (col == 4)
		return (solve(map, line + 1, 0, ctr));
	num = 0;
	while (++num <= 4)
	{
		if (check_doubles_line(map, col, num) == 1
			&& check_doubles_col(map, line, num) == 1)
		{
			map[line][col] = num;
			if (check_ctr(map, line, col, ctr) == 1)
			{
				if (solve(map, line, col +1, ctr) == 1)
					return (1);
			}
		}
	}
	map[line][col] = 0;
	return (0);
}

void	def_map(int map[4][4])
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			map[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	get_contraintes(char *str, int ctr[16])
{
	int	i;

	i = 0;
	while (i < 32)
	{
		if (str[i] >= '1' && str[i] <= '4')
		{
			ctr[i / 2] = str[i] - '0';
			i += 2;
		}
		else
			break ;
	}
}

int	main(int argc, char **argv)
{	
	int	i;
	int	map[4][4];
	int	ctr[16];

	def_map(map);
	i = 0;
	if (argc == 2)
	{
		get_contraintes(argv[1], ctr);
		if (solve(map, 0, 0, ctr) == 1)
			print_puzzle_map(map);
		else
			write(1, "Error\n", 6);
	}
	else
		write(1, "Error\n", 6);
	return (0);
}
