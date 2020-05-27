/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/27 16:31:54 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*winner(void *param)
{
	t_philo	*philo;
	int		j;
	int lol;

	philo = (t_philo*)param;
	j = 0;
	while (j < philo->number_of_philosopher)
	{
		printf("J = %p  %d\n", philo->philo_win, j);
		sem_wait(philo->philo_win);
		printf("yeah\n");
		++j;
	}
	philo->dead = 2;
	return (NULL);
}

void	*loser(void *param)
{
	t_philo	*philo;
	philo = (t_philo*)param;
	usleep(9000);
	sem_wait(philo->die);
	philo->dead = 1;
	return (NULL);
}
