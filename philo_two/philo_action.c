/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 20:29:24 by avan-pra            #+#    #+#             */
/*   Updated: 2020/05/26 15:00:57 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

void		get_fork(t_philo *philo, t_timeval t_start)
{
	sem_wait(philo->mutext);
	display(t_start, philo->number, "has taken a fork");
	sem_wait(philo->mutext);
	display(t_start, philo->number, "has taken a fork");
}

void		release_fork(t_philo *philo)
{
	sem_post(philo->mutext);
	sem_post(philo->mutext);
}

void		eat(t_philo *philo, t_timeval t_start)
{
	display(t_start, philo->number, "is eating");
	usleep(philo->time_to_eat);
}

void		psleep(t_philo *philo, t_timeval t_start)
{
	display(t_start, philo->number, "is sleeping");
	usleep(philo->time_to_sleep);
	display(t_start, philo->number, "is thinking");
}
