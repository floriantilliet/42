/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 19:46:23 by ftilliet          #+#    #+#             */
/*   Updated: 2023/09/17 19:46:29 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

int	check_updown(int map[4][4], int col, int ctr[16])
{
	int	i;
	int	h;
	int	c;

	i = 0;
	h = 0;
	c = 0;
	while (i < 4)
	{
		if (map[i][col] > h)
		{
			h = map[i][col];
			c++;
		}
		else if (map[i][col] == 0)
			return (1);
		i++;
	}
	if (ctr[0 + col] != c)
		return (0);
	return (1);
}

int	check_downup(int map[4][4], int col, int ctr[16])
{
	int	i;
	int	h;
	int	c;

	i = 3;
	h = 0;
	c = 0;
	while (i >= 0)
	{
		if (map[i][col] > h)
		{
			h = map[i][col];
			c++;
		}
		else if (map[i][col] == 0)
			return (1);
		i--;
	}
	if (ctr[4 + col] != c)
		return (0);
	return (1);
}

int	check_leftright(int map[4][4], int line, int ctr[16])
{
	int	i;
	int	h;
	int	c;

	i = 0;
	h = 0;
	c = 0;
	while (i < 4)
	{
		if (map[line][i] > h)
		{
			h = map[line][i];
			c++;
		}
		else if (map[line][i] == 0)
			return (1);
		i++;
	}
	if (ctr[8 + line] != c)
		return (0);
	return (1);
}

int	check_rightleft(int map[4][4], int line, int ctr[16])
{
	int	i;
	int	h;
	int	c;

	i = 3;
	h = 0;
	c = 0;
	while (i >= 0)
	{
		if (map[line][i] > h)
		{
			h = map[line][i];
			c++;
		}
		else if (map[line][i] == 0)
			return (1);
		i--;
	}
	if (ctr[12 + line] != c)
		return (0);
	return (1);
}

int	check_ctr(int map[4][4], int line, int col, int ctr[16])
{
	if (check_updown(map, col, ctr) == 0)
		return (0);
	else if (check_downup(map, col, ctr) == 0)
		return (0);
	else if (check_rightleft(map, line, ctr) == 0)
		return (0);
	else if (check_leftright(map, line, ctr) == 0)
		return (0);
	return (1);
}
