/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/28 13:05:10 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*winner(void *param)
{
	t_philo	*philo;
	int		j;

	philo = (t_philo*)param;
	j = 0;
	while (j < philo->number_of_philosopher)
	{
		sem_wait(philo->philo_win);
		++j;
	}
	philo->dead = 2;
	return (NULL);
}

void	*loser(void *param)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo*)param;
	sem_wait(philo->die);
	i = 0;
	while (i < philo->number_of_philosopher)
		kill(philo->pid[i++], SIGINT);
	philo->dead = 1;
	return (NULL);
}
