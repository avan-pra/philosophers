/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:33:45 by avan-pra          #+#    #+#             */
/*   Updated: 2020/09/29 14:33:46 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void		get_fork(t_philo *philo, t_timeval t_start)
{
	pthread_mutex_lock(philo->mutext1);
	pthread_mutex_lock(philo->output);
	display(t_start, philo->number, "has taken a fork");
	pthread_mutex_unlock(philo->output);
	pthread_mutex_lock(philo->mutext2);
	pthread_mutex_lock(philo->output);
	display(t_start, philo->number, "has taken a fork");
	pthread_mutex_unlock(philo->output);
}

void		release_fork(t_philo *philo)
{
	pthread_mutex_unlock(philo->mutext1);
	pthread_mutex_unlock(philo->mutext2);
}

void		eat(t_philo *philo, t_timeval t_start)
{
	pthread_mutex_lock(philo->output);
	display(t_start, philo->number, "is eating");
	pthread_mutex_unlock(philo->output);
	usleep(philo->time_to_eat);
}

void		psleep(t_philo *philo, t_timeval t_start)
{
	pthread_mutex_lock(philo->output);
	display(t_start, philo->number, "is sleeping");
	pthread_mutex_unlock(philo->output);
	usleep(philo->time_to_sleep);
	pthread_mutex_lock(philo->output);
	display(t_start, philo->number, "is thinking");
	pthread_mutex_unlock(philo->output);
}
