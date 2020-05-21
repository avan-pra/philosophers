#include "phile_one.h"

void copy_struct(t_philo *paste, t_philo copy)
{
	paste->number_of_philosopher = copy.number_of_philosopher;
	paste->number_of_time_each_philosophers_must_eat = copy.number_of_time_each_philosophers_must_eat;
	paste->time_to_die = copy.time_to_die;
	paste->time_to_eat = copy.time_to_eat;
	paste->time_to_sleep = copy.time_to_sleep;
	paste->t_start = copy.t_start;
}

void init_mutex(pthread_mutex_t *mutex, int nbr, pthread_mutex_t mort)
{
	int i = 0;

	while (i < nbr)
	{
		pthread_mutex_init(&mutex[i], NULL);
		++i;
	}
}

int create_start_philo(int nbr, t_philo philo)
{
	t_philo arr[nbr];
	pthread_t th[nbr];
	pthread_mutex_t mutext[philo.number_of_philosopher];
	pthread_mutex_t mort;
	int j;

	j = 0;
	init_mutex(mutext, philo.number_of_philosopher, mort);
	pthread_mutex_init(&mort, NULL);
	pthread_mutex_lock(&mort);
	gettimeofday(&philo.t_start, NULL);
	philo.dead = 0;
	while (j < philo.number_of_philosopher)
	{
		copy_struct(&arr[j], philo);
		arr[j].dead = 0;
		arr[j].number = j;

		arr[j].die = &mort;
		arr[j].mutext1 = &mutext[j];
		arr[j].mutext2 = (j + 1 == philo.number_of_philosopher) ?
			&mutext[0]: &mutext[j + 1];

		pthread_create(&th[j], NULL, &ft_philosopher, &arr[j]);
		usleep(5000);
		++j;
	}

	pthread_t win;
	pthread_t lose;
	philo.th = (pthread_t*)&th;
	philo.die = &mort;
	pthread_create(&win, NULL, &winner, &philo);
	pthread_create(&lose, NULL, &loser, &philo);

	while (1)
	{
		if (philo.dead == 1)
		{
			printf("End of simulation : one of the philosophers died\n");
			return (1);
		}
		else if (philo.dead == 2)
		{
			printf("End of simulation : philosophers ate enough times\n");
			return (0);
		}
		usleep(1000);
	}
}

int main(int argc, char **argv)
{
	t_philo philo;
	int j;

	srand(time(0));
	if (fill_and_error(&philo, argv, argc) == 1)
		return (1);
	return (create_start_philo(philo.number_of_philosopher, philo));
}
