/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/26 15:01:06 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

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
	int		i;

	philo = (t_philo*)param;
	sem_wait(philo->die);
	i = 0;
	while (i < philo->number_of_philosopher)
		pthread_detach(philo->th[i++]);
	philo->dead = 1;
	return (NULL);
}
