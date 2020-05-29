/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/27 16:13:28 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <fcntl.h>
# include <semaphore.h>

typedef struct timeval	t_timeval;

typedef struct		s_philo
{
	int				number_of_philosopher;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_time_each_philosophers_must_eat;
	int				number;
	int				dead;
	int				eat;
	sem_t			*mutext;
	sem_t			*die;
	sem_t			*philo_win;
	pthread_t		*th;
	struct timeval	t_start;
}					t_philo;

typedef struct		s_dish
{
	char			*str;
	char			*tmp;
	char			*toi;
}					t_dish;

typedef struct		s_creat
{
	pthread_mutex_t	mort;
	int				j;
	pthread_t		win;
	pthread_t		lose;
}					t_creat;

char				*ft_itoa(long nb);
int					ft_strlen(char *str);
int					ft_atoi(const char *str);
int					fill_and_error(t_philo *philo, char **argv, int argc);
void				*ft_philosopher(void *param);
void				*winner(void *param);
void				*loser(void *param);
t_timeval			diff_time(t_timeval t1, t_timeval t2);
char				*join(char *s1, char *s2);
void				display(t_timeval t_start, int philo, char *msg);
void				*monitoring(void *param);
void				get_fork(t_philo *philo, t_timeval t_start);
void				release_fork(t_philo *philo);
void				eat(t_philo *philo, t_timeval t_start);
int					psleep(t_philo *philo, t_timeval t_start);

#endif
