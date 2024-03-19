/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftilliet <ftilliet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 17:42:37 by ftilliet          #+#    #+#             */
/*   Updated: 2024/03/19 12:18:26 by ftilliet         ###   ########.fr       */
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
