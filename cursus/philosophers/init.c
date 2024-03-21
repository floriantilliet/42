/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:42:31 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/21 10:04:02 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init_data(t_data *data, char **av, int ac)
{
	if (ac == 5)
		(*data).nb_of_meals = -1;
	else
	{
		(*data).nb_of_meals = ft_atoi(av[5]);
	}
	(*data).time_to_eat = ft_atoi(av[3]);
	(*data).time_to_sleep = ft_atoi(av[4]);
	(*data).time_to_die = ft_atoi(av[2]);
	(*data).is_dead = 0;
	(*data).nb_of_philos = ft_atoi(av[1]);
	if (ft_atoi(av[1]) % 2 != 0)
		(*data).time_to_think = ((*data).time_to_eat * 2
				- (*data).time_to_sleep) * 0.42;
	else
		(*data).time_to_think = (2 * ft_atoi(av[1]) / 10) * 0.42;
}

int	init_mutexes(t_data *data, int nb)
{
	int	i;

	data->mutexes = malloc(sizeof(pthread_mutex_t) * nb);
	if (!data->mutexes)
		return (0);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&(data->mutexes)[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->death, NULL);
	pthread_mutex_init(&data->readiness, NULL);
	return (1);
}

int	init_philos(t_philo **philos, t_data *data, int nb)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * nb);
	if (!*philos)
		return (0);
	data->nb_of_philos = nb;
	i = 0;
	while (i < nb)
	{
		(*philos)[i].meals_to_eat = data->nb_of_meals;
		(*philos)[i].r_fork = &data->mutexes[i];
		(*philos)[i].l_fork = &data->mutexes[(i + 1) % nb];
		(*philos)[i].data = data;
		(*philos)[i].id = i + 1;
		(*philos)[i].time_last_meal = 0;
		i++;
	}
	return (1);
}
