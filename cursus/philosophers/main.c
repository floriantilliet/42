/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:09:06 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/07 12:52:56 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_args(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (i < ac)
	{
		j = 1;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) || ft_atoi(av[i]) <= 0)
				return (ft_putendl_fd("Error", 2), 0);
			j++;
		}
		i++;
	}
	return (1);
}

void init_mutexes(pthread_mutex_t *mutexes, int nb)
{
	mutexes = malloc(sizeof(pthread_mutex_t) * nb);
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		i++;
	}
}

void init_philos(t_philo *philos, t_data data, int nb)
{
	philos = malloc(sizeof(t_philo) * nb);
	int	i;

	i = 0;
	while (i < nb)
	{
		philos[i].meals_eaten = 0;
		philos[i].is_dead = 0;
		philos[i].r_fork = &data.mutexes[i];
		philos[i].l_fork = &data.mutexes[(i+1) % nb];
		i++;
	}
}

void thread_create(t_philo *philos, t_data data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_create(&philos[i].thread, NULL, routine, &data);
		i++;
	}
	i = 0;
	while (i < nb)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void *routine(void *arg)
{   
    t_philo *philo = (t_philo *)philo;

	while(!(philo->data->is_dead))
	{
		pthread_mutex_lock(philo->r_fork);
		pthread_mutex_lock(philo->l_fork);
		eat();
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		sleep();
		think();
	}
}

void init_data(t_data data, char **av, int ac)
{
	if (ac == 5)
		data.nb_of_meals = -1;
	else
		data.nb_of_meals = ft_atoi(av[6]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	data.time_to_die = ft_atoi(av[2]);
	data.nb_of_philos = ft_atoi(av[1]);
}

int	main(int ac, char **av)
{	
	t_data data;
	t_philo *philos;
	
    if (ac != 5 && ac != 6)
        return (ft_putendl_fd("Error", 2), 0);
    if (!check_args(ac, av))
    {
        return (0);
    }
	init_data(data, av, ac);
	data.mutexes = NULL;
	init_mutexes(data.mutexes, ft_atoi(av[1]));
	init_philos(philos, data, ft_atoi(av[1]));
	
	return (0);
}
