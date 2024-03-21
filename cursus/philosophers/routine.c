/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:42:24 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/21 09:29:40 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->time);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->time);
	print_state("is eating", philo);
	ft_smartusleep(philo->data->time_to_eat, philo->data);
	if (philo->meals_to_eat > 0)
	{
		philo->meals_to_eat--;
	}
}

void	dream(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_smartusleep(philo->data->time_to_sleep, philo->data);
}

void	think(t_philo *philo)
{
	print_state("is thinking", philo);
	ft_smartusleep(philo->data->time_to_think, philo->data);
}

void	philo_actions(t_philo *philo)
{
	eat(philo);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
	dream(philo);
	think(philo);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!(philo->data->ready))
		;
	while (!(philo->data->is_dead))
	{
		if (philo->id % 2 == 0)
		{
			pthread_mutex_lock(philo->l_fork);
			print_state("has taken a fork", philo);
			pthread_mutex_lock(philo->r_fork);
			print_state("has taken a fork", philo);
		}
		else
		{
			pthread_mutex_lock(philo->r_fork);
			print_state("has taken a fork", philo);
			pthread_mutex_lock(philo->l_fork);
			print_state("has taken a fork", philo);
		}
		philo_actions(philo);
	}
	return (arg);
}
