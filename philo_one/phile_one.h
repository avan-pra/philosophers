#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct	s_philo
{
	int					number_of_philosopher;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_each_philosophers_must_eat;
	int					number;
	int					dead;
	pthread_mutex_t	*mutext1;
	pthread_mutex_t	*mutext2;
	struct timeval			t_start;
	
}				t_philo;

int		ft_atoi(const char *str);
int		fill_and_error(t_philo *philo, char **argv, int argc);

#endif
