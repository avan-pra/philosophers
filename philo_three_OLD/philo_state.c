#include "philo_three.h"

void *winner(void *param)
{
	t_philo *philo;
	int j = 0;

	philo = (t_philo*)param;
	while (j < philo->number_of_philosopher)
	{
		pthread_join(philo->th[j], NULL);
		++j;
	}
	philo->dead = 2;
	return (NULL);
}

void *loser(void *param)
{
	t_philo *philo;

	philo = (t_philo*)param;
	sem_wait(philo->die);
	usleep(8000);
	sem_post(philo->die);
	philo->dead = 1;
	return (NULL);
}
