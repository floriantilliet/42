/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: udumas <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:18:24 by udumas            #+#    #+#             */
/*   Updated: 2023/09/27 19:41:40 by udumas           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_libr.h"

int	main(int argc, char **argv)
{
	int		i;
	char	*map;

	i = 0;
	if (argc == 1)
	{
		map = ft_stdin();
		if (maperror(map) == 0)
			write(2, "map error\n", 10);
		else
			get_and_solve(map);
		free(map);
	}
	else
	{
		while (++i < argc)
		{
			map = ft_read(argv[i]);
			if (maperror(map) == 0)
				write(2, "map error\n", 10);
			else
				get_and_solve(map);
		}
	}
	return (0);
}
