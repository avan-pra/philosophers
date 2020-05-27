/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 20:29:24 by velovo            #+#    #+#             */
/*   Updated: 2020/05/27 14:21:20 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

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
