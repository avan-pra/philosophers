#ifndef PHILO_ONE_H
# define PHILO_ONE_H

#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <semaphore.h>

typedef struct timeval t_timeval;

typedef struct	s_philo
{
	int					number_of_philosopher;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_time_each_philosophers_must_eat;
	int					number;
	int					dead;
	int					eat;
	struct timeval			t_start;
	
}				t_philo;

char   	*ft_itoa(unsigned long long nb);
int		ft_strlen(char *str);
int		ft_atoi(const char *str);
int		fill_and_error(t_philo *philo, char **argv, int argc);
void	*ft_philosopher(void *param);
void	*winner(void *param);
void	*loser(void *param);

#endif
