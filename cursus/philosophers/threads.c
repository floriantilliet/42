#include  "philosophers.h"

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
