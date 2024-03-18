/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:09:06 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/18 19:15:38 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **av)
{
	t_data	data;
	t_philo	*philos;

	philos = NULL;
	if (ac != 5 && ac != 6)
		return (ft_putendl_fd("Error", 2), 0);
	if (!check_args(ac, av))
	{
		return (0);
	}
	init_data(&data, av, ac);
	init_mutexes(&data, ft_atoi(av[1]));
	init_philos(&philos, &data, ft_atoi(av[1]));
	thread_create(philos, ft_atoi(av[1]));
	return (0);
}
