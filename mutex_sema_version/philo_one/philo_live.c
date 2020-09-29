/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_live.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/26 15:34:19 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

t_philo		*setup_philo(void *param)
{
	pthread_t	moni;
	t_timeval	t_now;
	t_philo		*philo;

	philo = (t_philo*)param;
	philo->ntime_eat = 0;
	philo->last_time_eat = philo->t_start;
	gettimeofday(&t_now, NULL);
	philo->last_time_eat = diff_time(philo->t_start, t_now);
	pthread_create(&moni, NULL, &monitoring, philo);
	return (philo);
}

void		get_time_eat(t_philo *philo)
{
	t_timeval t_now;

	gettimeofday(&t_now, NULL);
	philo->last_time_eat = diff_time(philo->t_start, t_now);
}

void		*ft_philosopher(void *param)
{
	t_philo		*philo;
	pthread_t	moni;

	philo = setup_philo(param);
	while (philo->ntime_eat < philo->number_of_time_each_philosophers_must_eat
		|| philo->number_of_time_each_philosophers_must_eat == -1)
	{
		get_fork(philo, philo->t_start);
		get_time_eat(philo);
		eat(philo, philo->t_start);
		++philo->ntime_eat;
		release_fork(philo);
		psleep(philo, philo->t_start);
	}
	return (NULL);
}
