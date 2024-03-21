/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:42:46 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/21 09:30:29 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_mutexes(t_data *data, int nb)
{
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_destroy(&data->mutexes[i]);
		i++;
	}
	pthread_mutex_destroy(&data->time);
	pthread_mutex_destroy(&data->print);
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->readiness);
	free(data->mutexes);
}

void	create_threads(t_philo *philos, int nb)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&philos->data->time);
	while (i < nb)
	{
		philos[i].time_last_meal = philos->data->t0;
		i++;
	}
	pthread_mutex_unlock(&philos->data->time);
	i = 0;
	while (i < nb)
	{
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		i++;
	}
}

void	join_threads(t_philo *philos, pthread_t observer, int nb)
{
	int	i;

	pthread_join(observer, NULL);
	i = 0;
	while (i < nb)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
}

void	single_philo(t_philo *philo)
{
	ft_smartusleep(philo->data->time_to_die, philo->data);
	pthread_mutex_lock(&philo->data->death);
	print_state("died", philo);
	philo->data->is_dead = 1;
	pthread_mutex_unlock(&philo->data->death);
}

void	thread_create(t_philo *philos, int nb)
{
	pthread_t	observer;

	observer = 0;
	pthread_mutex_lock(&philos->data->readiness);
	philos->data->ready = 0;
	pthread_mutex_unlock(&philos->data->readiness);
	pthread_mutex_lock(&philos->data->time);
	philos->data->t0 = get_current_time();
	pthread_mutex_unlock(&philos->data->time);
	if (nb == 1)
		single_philo(philos);
	else
	{
		pthread_create(&observer, NULL, &monitor, philos);
		create_threads(philos, nb);
		pthread_mutex_lock(&philos->data->readiness);
		philos->data->ready = 1;
		pthread_mutex_unlock(&philos->data->readiness);
	}
	join_threads(philos, observer, nb);
	destroy_mutexes(philos->data, nb);
	free(philos);
}
