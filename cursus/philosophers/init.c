#include "philosophers.h"

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

void	init_mutexes(t_data *data, int nb)
{
	int	i;

	data->mutexes = malloc(sizeof(pthread_mutex_t) * nb);
	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&(data->mutexes)[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->time, NULL);
	pthread_mutex_init(&data->death, NULL);
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
