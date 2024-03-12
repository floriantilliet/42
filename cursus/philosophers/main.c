/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:09:06 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/12 17:00:05 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

size_t	get_current_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		write(2, "gettimeofday() error\n", 22);
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

int	ft_usleep(size_t milliseconds)
{
	size_t	start;

	start = get_current_time();
	while ((get_current_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

void	print_state(char *str, t_philo *philo)
{
	size_t time;

	time = get_current_time() - philo->data->t0;
	if (!philo->data->is_dead)
		printf("%zu %d %s\n", time, philo->id, str);
}

int	check_args(int ac, char **av)
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

void	init_mutexes(pthread_mutex_t **mutexes, int nb)
{
	int	i;

	*mutexes = malloc(sizeof(pthread_mutex_t) * nb);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&(*mutexes)[i], NULL);
		i++;
	}
}

#include <stdlib.h> // Add missing include statement

void	init_philos(t_philo **philos, t_data data, int nb)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * nb);
	i = 0;
	while (i < nb)
	{
		(*philos)[i].meals_eaten = 0;
		(*philos)[i].r_fork = &data.mutexes[i];
		(*philos)[i].l_fork = &data.mutexes[(i + 1) % nb];
		(*philos)[i].data = &data;
		(*philos)[i].id = i + 1;
		i++;
	}
}

void	eat(t_philo *philo)
{
	print_state("is eating", philo);
	ft_usleep(philo->data->time_to_eat);
	philo->meals_eaten++;
	philo->time_last_meal = get_current_time();
}

void	dream(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_state("is thinking", philo);
	// ft_usleep(philo->data->time_to_think);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(philo->data->is_dead))
	{
		pthread_mutex_lock(philo->r_fork);
		print_state("has taken a fork", philo);
		pthread_mutex_lock(philo->l_fork);
		print_state("has taken a fork", philo);
		eat(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		dream(philo);
		think(philo);
	}
	return (arg);
}

void	*monitor(void *arg)
{
	t_philo	*philos;
	int i = 0;

	philos = (t_philo *)arg;
	philos->data->t0 = get_current_time();

	while (1)
	{

		i = 0;
		while (i < philos->data->nb_of_philos)
		{
			// if (get_current_time() - (&philos)[i]->time_last_meal >= philos->data->time_to_die)
			// {
			// 	print_state("died", &philos[i]);
			// 	philos->data->is_dead = 1;
			// 	return (NULL);
			// }
			i++;
		}
	}
}

void	thread_create(t_philo *philos, int nb)
{
	int	i;
	pthread_t observer = 0;

	pthread_create(&observer , NULL, &monitor, philos);
	i = 0;
	while (i < nb)
	{
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		i++;
	}
	pthread_join(observer, NULL);
	i = 0;
	while (i < nb)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	init_data(t_data *data, char **av, int ac)
{
	if (ac == 5)
		(*data).nb_of_meals = -1;
	else
		(*data).nb_of_meals = ft_atoi(av[6]);
	(*data).time_to_eat = ft_atoi(av[3]);
	(*data).time_to_sleep = ft_atoi(av[4]);
	(*data).time_to_die = ft_atoi(av[2]);
	// (*data).time_to_think = 
	(*data).nb_of_philos = ft_atoi(av[1]);
}

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
	init_mutexes(&data.mutexes, ft_atoi(av[1]));
	init_philos(&philos, data, ft_atoi(av[1]));
	thread_create(philos, ft_atoi(av[1]));
	return (0);
}
