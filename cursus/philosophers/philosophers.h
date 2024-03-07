/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:24:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/07 10:29:17 by ftilliet         ###   ########.fr       */
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
}					t_philo;

typedef struct s_data
{
    int time_to_eat;
    int time_to_sleep;
    int time_to_think;
    int time_to_die;
    int t0;

    t_philo *philos;
}					t_data;

#endif