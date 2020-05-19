#include "phile_one.h"

int try_eat(t_philo *philo)
{
	int i;

	if (pthread_mutex_trylock(philo->mutext1) != 0)
	{
		return (-1);
	}
	if (pthread_mutex_trylock(philo->mutext2) != 0)
	{
		pthread_mutex_unlock(philo->mutext1); //virer car il lock la fourchette et tu son mate si ce dernier peut manger, faire un thread de monitoring pour chaque philo, faire mutex pour checker la mort d'un mec
		return (-1);
	}
	//printf("JE MAGE SAMER  %d\n", philo->number);
	return (0);
}

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

// void	*ft_philosopher(void *param)
// {
// 	t_philo *philo;
// 	int j;
// 	t_timeval t_start;
// 	t_timeval last_time_eat;
// 	t_timeval t_now;
// 	t_timeval t_s;
// 	t_timeval t_time;
// 	int state; // 0 = philo / 1 = eat / 2 = sleep

// 	philo = (t_philo*)param;
// 	t_start = philo->t_start;
// 	gettimeofday(&t_now, NULL);
// 	t_now = diff_time(t_start, t_now);
// 	last_time_eat = t_now;
// 	state = 0;
// 	printf("Lancement du philosophe %d a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
// 	j = 0;
// 	while (j < philo->number_of_time_each_philosophers_must_eat)
// 	{
// 		gettimeofday(&t_now, NULL);
// 		t_now = diff_time(t_start, t_now);

// 		if (state == 0) // il philo
// 		{
// 			t_time = diff_time(last_time_eat, t_now);
// 			if (t_time.tv_sec * 1000000 + t_time.tv_usec > philo->time_to_die)
// 			{
// 				printf("Philosophe %d decede a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
// 				philo->dead = 1;
// 				return(NULL);
// 			}
// 			if (try_eat(philo) == 0) //si il reussi
// 			{
// 				state = 1;
// 				printf("Philosophe %d mange a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
// 				t_s = t_now;
// 			}
// 		}
// 		else if (state == 1) //il mange
// 		{
// 			t_time = diff_time(t_s, t_now);
// 			if (t_time.tv_sec * 1000000 + t_time.tv_usec >= philo->time_to_eat)
// 			{
// 				last_time_eat = t_now;
// 				printf("Philosophe %d a fini de manger a %ld:%.6ld et va dormir\n", philo->number, t_now.tv_sec, t_now.tv_usec);
// 				pthread_mutex_unlock(philo->mutext1);
// 				pthread_mutex_unlock(philo->mutext2);
// 				state = 2;
// 				j++;
// 				t_s = t_now;
// 			}
// 		}
// 		else if (state == 2) //il dort
// 		{
// 			t_time = diff_time(last_time_eat, t_now);
// 			if (t_time.tv_sec * 1000000 + t_time.tv_usec > philo->time_to_die)
// 			{
// 				printf("Philosophe %d decede a %ld:%.6ld\n", philo->number, t_now.tv_sec, t_now.tv_usec);
// 				philo->dead = 1;
// 				return(NULL);
// 			}
// 			t_time = diff_time(t_s, t_now);
// 			if (t_time.tv_sec * 1000000 + t_time.tv_usec >= philo->time_to_sleep)
// 			{
// 				printf("Philosophe %d a fini de dormir a %ld:%.6ld et va philosopher\n", philo->number, t_now.tv_sec, t_now.tv_usec);
// 				state = 0;
// 			}
// 		}
// 		usleep(1000);
// 	}
// 	philo->dead = 2;
// 	return (NULL);
// }

// void monitoring()
// {
// 	int last_time_eat = 0;

// 	if (philo == 1)
// 	{
// 		last_time_eat = time_now;
// 	}
// 	else if (philo->eat == 0 && last_time_eat > time_to die)
// 	{
// 		//il ets mort
// 	}
// }

// void philo()
// {
// 	//call thread monitor; monitoring()
// 	while (pas finit de mager)
// 	{
// 		get_fork();
// 		eat();
// 		{
// 			philo->eat = 1;
// 			sleep(time_to_eat);
// 		}
// 		dsleep();
// 	}
// }

void *monitoring(void *param)
{
	t_philo *philo;
	t_timeval last_time_eat = timenow;

	philo = (t_philo*)param;
	while (1)
	{
		if (philo->eat == 1)
		{
			last_time_eat = timenow;
		}
		else if (philo->eat == 0 && last_time_eat > philo->time_to_die)
		{
			philo->dead = 1; //bon en vrai faut changer la methode de mort avec des mutex mais ca je le ferai moi
		}
		usleep(1000);
	}
}

void get_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->mutext1);
	//write(1, "i took a fork\n", 14);
	printf("Philo nbr: %d took the first fork\n", philo->number);
	pthread_mutex_lock(philo->mutext2);
	//write(1, "i took a second fork\n", 21);
	printf("Philo nbr: %d took the second fork\n", philo->number);
}

void release_fork(t_philo *philo)
{
	printf("Philo nbr: %d released both fork\n", philo->number);
	pthread_mutex_unlock(philo->mutext1);
	pthread_mutex_unlock(philo->mutext2);
}

void eat(t_philo *philo)
{
	philo->eat = 1;
	printf("Philo nbr: %d is now eating\n", philo->number);
	usleep(philo->time_to_eat);
	philo->eat = 0;
}

void psleep(t_philo *philo)
{
	printf("Philo nbr: %d is now sleeping\n", philo->number);
	usleep(philo->time_to_sleep);
	printf("Philo nbr: %d is now thinking\n", philo->number);
}

void	*ft_philosopher(void *param)
{
	t_philo *philo;
	int ntime_eat;

	philo = (t_philo*)param;
	ntime_eat = 0;
	while (ntime_eat < philo->number_of_time_each_philosophers_must_eat)
	{
		get_fork(philo);
		eat(philo);
		release_fork(philo);
		psleep(philo);
		++ntime_eat;
	}
	philo->dead = 2;
	return (NULL);
}
