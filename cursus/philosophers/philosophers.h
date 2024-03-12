/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:24:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/12 17:09:31 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				meals_eaten;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	int				id;
	size_t				time_last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	size_t				time_to_die;
	size_t				t0;
	int				nb_of_philos;
	int				nb_of_meals;
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;
}					t_data;

#endif