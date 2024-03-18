#include "philosophers.h"

void	*monitor(void *arg)
{
	t_philo	*philos;
	int		i;
	size_t	time;
	int		count;

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
		while (i < philos->data->nb_of_philos)
		{
			if (philos[i].meals_to_eat == 0)
			{
				count++;
				// printf("%d\n", count);
			}
			if (count == philos[i].data->nb_of_philos)
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
