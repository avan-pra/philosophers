#include "phile_one.h"

void	*ft_philosopher(void *param)
{
	t_philo *philo;
	int j;

	philo = (t_philo*)param;
	//printf("JE SUIS LE NOUMERO %d\n", philo->number);
	j = 0;
	while (j < philo->number_of_time_each_philosophers_must_eat)
	{
		usleep(philo->time_to_eat);
		if (rand() % 1000 == 1)
		{
			philo->dead = 1;
			return (philo);
		}
		++j;
	}
	philo->dead = 2;
	return (NULL);
}

void copy_struct(t_philo *paste, t_philo copy)
{
	paste->number_of_philosopher = copy.number_of_philosopher;
	paste->number_of_time_each_philosophers_must_eat = copy.number_of_time_each_philosophers_must_eat;
	paste->time_to_die = copy.time_to_die;
	paste->time_to_eat = copy.time_to_eat;
	paste->time_to_sleep = copy.time_to_sleep;
}

void create_start_philo(int nbr, t_philo philo)
{
	t_philo arr[nbr];
	pthread_t th[nbr];
	int j;

	j = 0;
	printf("%d\n", nbr);
	while (j < philo.number_of_philosopher)
	{
		copy_struct(&arr[j], philo);
		arr[j].dead = 0;
		arr[j].number = j;
		pthread_create(&th[j], NULL, &ft_philosopher, &arr[j]);
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
