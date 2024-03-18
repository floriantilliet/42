/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:09:06 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/18 16:04:05 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_atoi(const char *str)
{
	int	signe;
	int	result;

	signe = 1;
	result = 0;
	while ((*str <= 13 && *str >= 9) || *str == ' ')
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			signe *= -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * signe);
}

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

void	ft_putendl_fd(char *str, int fd)
{
	if (fd != -1 && str != NULL)
	{
		while (*str != '\0')
		{
			write(fd, str, 1);
			str++;
		}
		write(fd, "\n", 1);
	}
}

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
	size_t	time;

	pthread_mutex_lock(&philo->data->time);
	time = get_current_time() - philo->data->t0;
	pthread_mutex_unlock(&philo->data->time);
	if (!philo->data->is_dead)
	{
		pthread_mutex_lock(&philo->data->print);
		printf("%zu %d %s\n", time, philo->id, str);
		pthread_mutex_unlock(&philo->data->print);
	}
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

void	init_philos(t_philo **philos, t_data data, int nb)
{
	int	i;

	*philos = malloc(sizeof(t_philo) * nb);
	data.nb_of_philos = nb;
	i = 0;
	while (i < nb)
	{
		(*philos)[i].meals_to_eat = data.nb_of_meals;
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
	if(philo->meals_to_eat > 0)
	{
		philo->meals_to_eat--;
		// printf("%d has %d meals to eat left \n", philo->id, philo->meals_to_eat);
	}
	pthread_mutex_lock(&philo->data->time);
	philo->time_last_meal = get_current_time();
	pthread_mutex_unlock(&philo->data->time);
}

void	dream(t_philo *philo)
{
	print_state("is sleeping", philo);
	ft_usleep(philo->data->time_to_sleep);
}

void	think(t_philo *philo)
{
	print_state("is thinking", philo);
	ft_usleep(philo->data->time_to_think);
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
	int		i;
	size_t	time;
	int count;

	i = 0;
	philos = (t_philo *)arg;
	// philos->data->t0 = get_current_time();
	while (1)
	{
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
				return (NULL);
			}
			i++;
		}
		i = 0;
		count = 0;
		while(i < philos->data->nb_of_philos)
		{
			if (philos[i].meals_to_eat == 0)
			{
				count++;
				// printf("%d\n", count);
			}
			if(count == philos[i].data->nb_of_philos)
			{
				pthread_mutex_lock(&philos->data->death);
				philos->data->is_dead = 1;
				pthread_mutex_unlock(&philos->data->death);
				return (NULL);
			}
			i++;
		}
	}
}

void	thread_create(t_philo *philos, int nb)
{
	int			i;
	pthread_t	observer;

	observer = 0;
	philos->data->ready = 0;
	philos->data->t0 = get_current_time();
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
}

void	init_data(t_data *data, char **av, int ac)
{
	if (ac == 5)
		(*data).nb_of_meals = -1;
	else
	{
		(*data).nb_of_meals = ft_atoi(av[5]);
	}
	(*data).time_to_eat = ft_atoi(av[3]);
	(*data).time_to_sleep = ft_atoi(av[4]);
	(*data).time_to_die = ft_atoi(av[2]);
	(*data).time_to_think = ((*data).time_to_eat * 2 - (*data).time_to_sleep)
		* 0.42;
	(*data).is_dead = 0;
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
	pthread_mutex_init(&data.print, NULL);
	pthread_mutex_init(&data.time, NULL);
	pthread_mutex_init(&data.death, NULL);
	init_philos(&philos, data, ft_atoi(av[1]));
	thread_create(philos, ft_atoi(av[1]));
	return (0);
}
