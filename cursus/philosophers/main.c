/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 11:09:06 by ftilliet          #+#    #+#             */
/*   Updated: 2024/02/26 17:26:20 by ftilliet         ###   ########.fr       */
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

void init_mutexes(pthread_mutex_t *mutex, int nb)
{
	mutex = malloc(sizeof(pthread_mutex_t) * nb);
	int	i;

	i = 0;
	while (i < nb)
	{
		pthread_mutex_init(&mutex[i], NULL);
		i++;
	}
}

void *routine(void *arg)
{   
    struct s_data *data = (struct s_data *)arg;

    pthread_mutex_lock(data->);
	pthread_mutex_lock(data->);
	eat();
    pthread_mutex_unlock(data->);
	pthread_mutex_unlock(data->);
	sleep();
	think();
}

int	main(int ac, char **av)
{	
	pthread_mutex_t	*mutex;
	pthread_t		*philo;
	
    if (ac != 5 && ac != 6)
        return (ft_putendl_fd("Error", 2), 0);
    if (!check_args(ac, av))
    {
        return (0);
    }
	mutex = NULL;
	init_mutexes(mutex, ft_atoi(av[1]));
	
	return (0);
}
