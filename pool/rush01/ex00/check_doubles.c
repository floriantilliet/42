/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_doubles.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:54:40 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/17 20:32:08 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	check_doubles_line(int map[4][4], int col, int num)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map[i][col] == num)
			return (0);
		i++;
	}
	return (1);
}

int	check_doubles_col(int map[4][4], int line, int num)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (map[line][i] == num)
			return (0);
		i++;
	}
	return (1);
}
