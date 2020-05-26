/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_monitoring.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 20:07:19 by velovo            #+#    #+#             */
/*   Updated: 2020/05/26 15:01:44 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

int			death_check(t_timeval last_time_eat, t_timeval t_now,
	t_philo *philo, t_timeval t_start)
{
	t_timeval	t_time;

	t_time = diff_time(last_time_eat, t_now);
	if (t_time.tv_sec * 1000000 + t_time.tv_usec >= philo->time_to_die)
	{
		display(t_start, philo->number, "died");
		philo->dead = 1;
		sem_post(philo->die);
		return (1);
	}
	return (0);
}

void		*monitoring(void *param)
{
	t_philo		*philo;
	t_timeval	t_now;
	t_timeval	t_start;
	t_timeval	last_time_eat;
	t_timeval	t_time;

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
			last_time_eat = t_now;
		else if (philo->eat == 0)
		{
			if (death_check(last_time_eat, t_now, philo, t_start) == 1)
				return (NULL);
		}
		usleep(1000);
	}
	return (NULL);
}
