/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:09:06 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/07 10:36:11 by ftilliet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int check_args(int ac, char **av)
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

void init_mutexes(pthread_mutex_t *mutexes, int nb)
{
	mutexes = malloc(sizeof(pthread_mutex_t) * nb);
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		i++;
	}
}

void init_philos(pthread_t *philos, int nb)
{
	
}

void *routine(void *arg)
{   
    struct s_data *data = (struct s_data *)arg;

	while(!dead)
	{
		pthread_mutex_lock(data->);
		pthread_mutex_lock(data->);
		eat();
		pthread_mutex_unlock(data->);
		pthread_mutex_unlock(data->);
		sleep();
		think();
	}
}

int	main(int ac, char **av)
{	
	pthread_mutex_t	*mutexes;
	pthread_t		*philos;
	
    if (ac != 5 && ac != 6)
        return (ft_putendl_fd("Error", 2), 0);
    if (!check_args(ac, av))
    {
        return (0);
    }
	mutexes = NULL;
	init_mutexes(mutexes, ft_atoi(av[1]));
	philos = malloc(sizeof(pthread_t) * ft_atoi(av[1]));
	
	return (0);
}
