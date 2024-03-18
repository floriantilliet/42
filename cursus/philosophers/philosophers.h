/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 17:24:13 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/18 18:02:53 by ftilliet         ###   ########.fr       */
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
	int				meals_to_eat;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_t		thread;
	int				id;
	size_t			time_last_meal;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_think;
	size_t			time_to_die;
	size_t			t0;
	int				nb_of_philos;
	int				nb_of_meals;
	int				is_dead;
	int				ready;
	t_philo			*philos;
	pthread_mutex_t	*mutexes;
	pthread_mutex_t	time;
	pthread_mutex_t	print;
	pthread_mutex_t	death;
}					t_data;

void				eat(t_philo *philo);
void				dream(t_philo *philo);
void				think(t_philo *philo);
void				*routine(void *arg);

void				init_data(t_data *data, char **av, int ac);
void				init_mutexes(t_data *data, int nb);
void				init_philos(t_philo **philos, t_data data, int nb);

size_t				get_current_time(void);
int					ft_usleep(size_t milliseconds);

int					ft_atoi(const char *str);
int					ft_isdigit(int c);
void				ft_putendl_fd(char *str, int fd);
void				print_state(char *str, t_philo *philo);
int					check_args(int ac, char **av);

int					death_checker(t_philo *philos);
int					meal_checker(t_philo *philos);
void				*monitor(void *arg);

void				thread_create(t_philo *philos, int nb);

#endif