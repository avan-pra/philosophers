/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 20:29:24 by velovo            #+#    #+#             */
/*   Updated: 2020/05/26 15:34:08 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		get_fork(t_philo *philo, t_timeval t_start)
{
	pthread_mutex_lock(philo->mutext1);
	display(t_start, philo->number, "has taken a fork");
	pthread_mutex_lock(philo->mutext2);
	display(t_start, philo->number, "has taken a fork");
}

void		release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutext1);
	pthread_mutex_unlock(philo->mutext2);
}

void		eat(t_philo *philo, t_timeval t_start)
{
	philo->eat = 1;
	display(t_start, philo->number, "is eating");
	usleep(philo->time_to_eat);
	philo->eat = 0;
}

int			psleep(t_philo *philo, t_timeval t_start)
{
	display(t_start, philo->number, "is sleeping");
	usleep(philo->time_to_sleep);
	if (philo->dead == 1)
		return (1);
	display(t_start, philo->number, "is thinking");
	return (0);
}