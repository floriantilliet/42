/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:42:46 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/18 18:59:12 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "philosophers.h"

void destroy_mutexes(t_data *data, int nb)
{
    int i;

    i = 0;
    while (i < nb)
    {
        pthread_mutex_destroy(&data->mutexes[i]);
        i++;
    }
    pthread_mutex_destroy(&data->time);
    pthread_mutex_destroy(&data->print);
    pthread_mutex_destroy(&data->death);
    free(data->mutexes);
}

void	thread_create(t_philo *philos, int nb)
{
	int			i;
	pthread_t	observer;

	observer = 0;
	philos->data->ready = 0;
    pthread_mutex_lock(&philos->data->time);
	philos->data->t0 = get_current_time();
    pthread_mutex_unlock(&philos->data->time);
	i = 0;
	while (i < nb)
	{
		philos[i].time_last_meal = philos->data->t0;
		i++;
	}
	pthread_create(&observer, NULL, &monitor, philos);
	i = 0;
	while (i < nb)
	{
		pthread_create(&philos[i].thread, NULL, &routine, &philos[i]);
		i++;
	}
	philos->data->ready = 1;
	pthread_join(observer, NULL);
	i = 0;
	while (i < nb)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
    destroy_mutexes(philos->data, nb);
    free(philos);
}
