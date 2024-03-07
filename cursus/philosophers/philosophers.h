/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:24:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/07 12:51:52 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include "libft/libft.h"
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_philo
{
	int				meals_eaten;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	t_data			*data;
}					t_philo;

typedef struct s_data
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	int				time_to_die;
	int				t0;
	int				nb_of_philos;
	int				nb_of_meals;
	int				is_dead;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;
}					t_data;

#endif