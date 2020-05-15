#include "phile_one.h"

typedef struct timeval t_timeval;

t_timeval diff_time(t_timeval t1, t_timeval t2)
{
    unsigned long time1;
    unsigned long time2;
    t_timeval ret;

    time1 = t1.tv_sec * 1000000 + t1.tv_usec;
    time2 = t2.tv_sec * 1000000 + t2.tv_usec;
    time2 -= time1;
    ret.tv_sec = time2 / 1000000;
    ret.tv_usec = (int) time2 - ret.tv_sec * 1000000;
	return (ret);
}

int try_eat(t_philo *philo)
{
	int i;

	if (pthread_mutex_trylock(philo->mutext1) != 0)
		return (-1);
	if (pthread_mutex_trylock(philo->mutext2) != 0)
	{
		pthread_mutex_unlock(philo->mutext1); //virer car il lock la fourchette et tu son mate si ce dernier peut manger, faire un thread de monitoring pour chaque philo, faire mutex pour checker la mort d'un mec
		return (-1);
	}
	//printf("JE MAGE SAMER  %d\n", philo->number);
	return (0);
}

void	*ft_philosopher(void *param)
{
	t_philo *philo;
	int j;
	t_timeval t_start;
	t_timeval last_time_eat;
	t_timeval t_now;
	t_timeval t_s;
	t_timeval t_time;
	int state; // 0 = philo / 1 = eat / 2 = sleep

	gettimeofday(&t_start, NULL);
	philo = (t_philo*)param;
	gettimeofday(&t_now, NULL);
	t_now = diff_time(t_start, t_now);
	last_time_eat = t_now;
	state = 0;
	printf("Lancement du philosophe %d a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
	j = 0;
	while (j < philo->number_of_time_each_philosophers_must_eat)
	{
		gettimeofday(&t_now, NULL);
		t_now = diff_time(t_start, t_now);

		if (state == 0) // il philo
		{
			t_time = diff_time(last_time_eat, t_now);
			if (t_time.tv_sec * 1000000 + t_time.tv_usec > philo->time_to_die)
			{
				printf("Philosophe %d decede a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
				philo->dead = 1;
				return(NULL);
			}
			if (try_eat(philo) == 0) //si il reussi
			{
				state = 1;
				printf("Philosophe %d mange a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
				t_s = t_now;
			}
		}
		else if (state == 1) //il mange
		{
			t_time = diff_time(t_s, t_now);
			if (t_time.tv_sec * 1000000 + t_time.tv_usec >= philo->time_to_eat)
			{
				last_time_eat = t_now;
				printf("Philosophe %d a fini de manger a %ld:%.6ld et va dormir\n", philo->number, t_now.tv_sec, t_now.tv_usec);
				pthread_mutex_unlock(philo->mutext1);
				pthread_mutex_unlock(philo->mutext2);
				state = 2;
				j++;
				t_s = t_now;
			}
		}
		else if (state == 2) //il dort
		{
			t_time = diff_time(last_time_eat, t_now);
			if (t_time.tv_sec * 1000000 + t_time.tv_usec > philo->time_to_die)
			{
				printf("Philosophe %d decede a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
				philo->dead = 1;
				return(NULL);
			}
			t_time = diff_time(t_s, t_now);
			if (t_time.tv_sec * 1000000 + t_time.tv_usec >= philo->time_to_sleep)
			{
				printf("Philosophe %d a fini de dormir a %ld:%.6ld et va philosopher\n", philo->number, t_now.tv_sec, t_now.tv_usec);
				state = 0;
			}
		}
		usleep(5000);
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
	int j;

	j = 0;
	pthread_mutex_t mutext[philo.number_of_philosopher];
	init_mutex(mutext, philo.number_of_philosopher);
	while (j < philo.number_of_philosopher)
	{
		copy_struct(&arr[j], philo);
		arr[j].dead = 0;
		arr[j].number = j;

		arr[j].mutext1 = &mutext[j];
		arr[j].mutext2 = (j + 1 == philo.number_of_philosopher) ?
			&mutext[0]: &mutext[j + 1];

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
