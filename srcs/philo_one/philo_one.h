/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/26 15:35:17 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <unistd.h>
# include <sys/time.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>

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
	size_t			ntime_eat;
	pthread_mutex_t *output;
	pthread_mutex_t	*mutext1;
	pthread_mutex_t	*mutext2;
	pthread_mutex_t	*die;
	pthread_t		*th;
	struct timeval	last_time_eat;
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
void				psleep(t_philo *philo, t_timeval t_start);
void				init_mutex(pthread_mutex_t *mutex, int nbr);

#endif
