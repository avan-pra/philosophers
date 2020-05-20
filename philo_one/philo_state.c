#include "phile_one.h"

void *winner(void *param)
{
	t_philo *philo;
	int j = 0;

	philo = (t_philo*)param;
	while (j < philo->number_of_philosopher)
	{
		pthread_join(*philo->th[j], NULL);
		++j;
	}
	philo->dead = 2;
	return (NULL);
}

void *loser(void *param)
{
	t_philo *philo;

	philo = (t_philo*)param;
	pthread_mutex_lock(philo->die);
	usleep(9000);
	pthread_mutex_unlock(philo->die);
	philo->dead = 1;
	return (NULL);
}