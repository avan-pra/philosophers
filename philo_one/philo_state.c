/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/26 15:34:52 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	*winner(void *param)
{
	t_philo	*philo;
	int		j;

	philo = (t_philo*)param;
	j = 0;
	while (j < philo->number_of_philosopher)
	{
		pthread_join(philo->th[j], NULL);
		++j;
	}
	philo->dead = 2;
	return (NULL);
}

void	*loser(void *param)
{
	t_philo	*philo;
	int i;

	philo = (t_philo*)param;
	pthread_mutex_lock(philo->die);
	i = 0;
	while (i < philo->number_of_philosopher)
		pthread_detach(philo->th[i++]);
	// pthread_mutex_unlock(philo->die);
	philo->dead = 1;
	return (NULL);
}
