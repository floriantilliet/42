/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:42:43 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/19 15:17:57 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	death_checker(t_philo *philos)
{
	int		i;
	size_t	time;

	i = 0;
	while (i < philos->data->nb_of_philos)
	{
		pthread_mutex_lock(&philos->data->time);
		time = get_current_time() - philos[i].time_last_meal;
		pthread_mutex_unlock(&philos->data->time);
		if (time >= philos[i].data->time_to_die)
		{
			pthread_mutex_lock(&philos->data->death);
			print_state("died", &philos[i]);
			philos->data->is_dead = 1;
			pthread_mutex_unlock(&philos->data->death);
			return (1);
		}
		i++;
	}
	return (0);
}

int	meal_checker(t_philo *philos)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < philos->data->nb_of_philos)
	{
		if (philos[i].meals_to_eat == 0)
			count++;
		if (count == philos[i].data->nb_of_philos)
		{
			pthread_mutex_lock(&philos->data->death);
			philos->data->is_dead = 1;
			pthread_mutex_unlock(&philos->data->death);
			return (1);
		}
		i++;
	}
	return (0);
}

void	*monitor(void *arg)
{
	t_philo	*philos;

	philos = (t_philo *)arg;
	while (1)
	{
		if (death_checker(philos))
			return (NULL);
		if (meal_checker(philos))
			return (NULL);
	}
}
