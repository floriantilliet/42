/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maperror.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:49:59 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 14:50:01 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"

int	is_good_carac(char c, char *sep)
{
	int	i;

	i = 0;
	while (sep[i] != '\0')
	{
		if (c == sep[i])
			return (1);
		i++;
	}
	return (0);
}

int	check_first_line(char *map)
{
	int	i;

	i = 0;
	while (map[i] != '\n')
	{
		if (map[i] < 32 || map[i] > 126)
			return (0);
		i++;
	}
	if (i < 4)
		return (0);
	return (i);
}

int	check_line2(char *map, char *sep)
{
	int	i;
	int	count_line;

	count_line = 0;
	i = check_first_line(map);
	while (map[i] != '\0')
	{
		if (map[i] == '\n' && map[i + 1] != '\0')
		{
			count_line++;
		}
		else if (is_good_carac(map[i], sep) == 0)
		{
			if (map[i] == '\n' && (map[i] < 32 || map[i] > 126))
				return (count_line);
			else
				return (0);
		}
		i++;
	}
	return (count_line);
}

int	check_line(char *map)
{
	int	i;
	int	j;
	int	count;

	j = 0;
	i = check_first_line(map) + 1;
	count = 0;
	while (map[i] != '\n' && map[i++] != '\0')
		count++;
	if (map[i] == '\0' && count == 0)
		return (0);
	while (map[++i] != '\0')
	{
		if (map[i] == '\n')
		{
			if (count != j)
				return (0);
			if (j == 0)
				return (0);
			j = -1;
		}
		j++;
	}
	return (i);
}

int	maperror(char *map)
{
	char	*sep;
	int		i;

	i = 1;
	if (map == NULL)
		i = 0;
	if (check_first_line(map) == 0)
		i = 0;
	sep = take_sep(map);
	if (sep == 0)
		i = 0;
	else if (check_line(map) == 0)
		i = 0;
	else if (check_line2(map, sep) == 0)
		i = 0;
	else if (check_line2(map, sep) != check_correcrow(map))
		i = 0;
	if (i == 0)
	{
		free(map);
		return (0);
	}
	return (1);
}
