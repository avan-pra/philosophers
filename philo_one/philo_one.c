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

void init_mutex(pthread_mutex_t *mutex, int nbr)
{
	int i = 0;

	while (i < nbr)
	{
		pthread_mutex_init(&mutex[i], NULL);
		++i;
	}
}

void create_start_philo(int nbr, t_philo philo)
{
	t_philo arr[nbr];
	pthread_t th[nbr];
	pthread_mutex_t mutext[philo.number_of_philosopher];
	int j;

	j = 0;
	init_mutex(mutext, philo.number_of_philosopher);
	gettimeofday(&philo.t_start, NULL);
	while (j < philo.number_of_philosopher)
	{
		copy_struct(&arr[j], philo);
		arr[j].dead = 0;
		arr[j].number = j;

		arr[j].mutext1 = &mutext[j];
		arr[j].mutext2 = (j + 1 == philo.number_of_philosopher) ?
			&mutext[0]: &mutext[j + 1];

		pthread_create(&th[j], NULL, &ft_philosopher, &arr[j]);
		usleep(1000);
		++j;
	}
	j = 0;
	while (1)
	{
		j = 0;
		while (j < philo.number_of_philosopher)
		{
			if (arr[j].dead == 1)
			{
				printf("philosophe nbr: %d est mort, arret\n", j);
				exit(1);
			}
			++j;
		}
		j = 0;
		while (arr[j].dead == 2)
		{
			if (j == philo.number_of_philosopher - 1)
			{
				printf("CONGRATULATION THEY WIN\n");
				exit(0);
			}
			++j;
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
	create_start_philo(philo.number_of_philosopher, philo);
	return (0);
}
