/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basefunc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:49:26 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 14:49:28 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"
#include <unistd.h>

char	*take_sep(char *map)
{
	int			i;
	int			j;
	int			k;
	static char	sep[4];

	j = 0;
	k = 0;
	i = check_first_line(map) - 3;
	while (k <= 3)
	{
		j = k + 1;
		while (j < 4)
		{
			if (map[i + j] == map[i + k])
				return (NULL);
			j++;
		}
		sep[k] = map[i + k];
		k++;
	}
	sep[3] = '\0';
	return (sep);
}

int	check_correcrow(char *map)
{
	int	i;
	int	j;
	int	nb;

	i = check_first_line(map) - 3;
	j = 0;
	nb = 0;
	while (j < i)
	{
		if (map[j] >= '0' && map[j] <= '9')
			nb = nb * 10 + (map[j] - '0');
		else
			return (0);
		j++;
	}
	return (nb);
}

int	skip_fline(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	return (i);
}

void	ft_putstr2(char *str, int line_len, int col_len)
{
	int	i;

	i = 0;
	write(1, &str[i], (line_len * (col_len + 1)));
}

void	ft_putstr(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	write(1, "\n", 1);
}
