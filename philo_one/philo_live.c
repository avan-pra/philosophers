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

void display(t_timeval t_start, int philo, char *msg)
{
	t_timeval t_time;
	gettimeofday(&t_time, NULL);
	t_time = diff_time(t_start, t_time);

	int time_ms = t_time.tv_sec * 1000 + t_time.tv_usec / 1000;
	printf("%.6d %d %s\n", time_ms, philo, msg);
}

void *monitoring(void *param)
{
	t_philo *philo;
	t_timeval t_now;
	t_timeval t_start;
	t_timeval last_time_eat;
	t_timeval t_time;
	philo = (t_philo*)param;
	t_start = philo->t_start;
	gettimeofday(&t_now, NULL);
	t_now = diff_time(t_start, t_now);
	last_time_eat = t_now;

	while (1)
	{
		gettimeofday(&t_now, NULL);
		t_now = diff_time(t_start, t_now);
		if (philo->eat == 1)
		{
			last_time_eat = t_now;
		}
		else if (philo->eat == 0)
		{
			t_time = diff_time(last_time_eat, t_now);

			if (t_time.tv_sec * 1000000 + t_time.tv_usec >= philo->time_to_die)
			{
				display(t_start, philo->number, "died");
				philo->dead = 1;
				pthread_mutex_unlock(philo->die);
				return (NULL);
			}
		}
		usleep(1000);
	}
}

void get_fork(t_philo *philo, t_timeval t_start)
{
	pthread_mutex_lock(philo->mutext1);
	display(t_start, philo->number, "has taken a fork");
	pthread_mutex_lock(philo->mutext2);
	display(t_start, philo->number, "has taken a fork");
}

void release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutext1);
	pthread_mutex_unlock(philo->mutext2);
}

void eat(t_philo *philo, t_timeval t_start)
{
	philo->eat = 1;
	display(t_start, philo->number, "is eating");
	usleep(philo->time_to_eat);
	philo->eat = 0;
}

int psleep(t_philo *philo, t_timeval t_start)
{
	display(t_start, philo->number, "is sleeping");
    usleep(philo->time_to_sleep);
    if (philo->dead == 1)
        return (1);
	display(t_start, philo->number, "is thinking");
    return (0);
}

void    *ft_philosopher(void *param)
{
    t_philo *philo;
    pthread_t moni;
    int ntime_eat;
	
	philo = (t_philo*)param;
    ntime_eat = 0;
    pthread_create(&moni, NULL, &monitoring, philo);
    while (ntime_eat < philo->number_of_time_each_philosophers_must_eat)
    {
        if (philo->dead == 1)
            return (NULL);
        get_fork(philo, philo->t_start);
        if (philo->dead == 1)
            return (NULL);
        eat(philo, philo->t_start);
        ++ntime_eat;
        if (philo->dead == 1)
            return (NULL);
        release_fork(philo);
        if (philo->dead == 1)
            return (NULL);
        if (psleep(philo, philo->t_start) == 1)
            return (NULL);
    }
    philo->eat = 1;
    return (NULL);
}