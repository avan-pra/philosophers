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

t_philo		*setup_philo(void *param, int *ntime_eat)
{
	pthread_t	moni;
	t_philo		*philo;

	philo = (t_philo*)param;
	*ntime_eat = 0;
	philo->eat = 0;
	pthread_create(&moni, NULL, &monitoring, philo);
	return (philo);
}

void		*ft_philosopher(void *param)
{
	t_philo		*philo;
	pthread_t	moni;
	int			ntime_eat;

	philo = setup_philo(param, &ntime_eat);
	while (ntime_eat < philo->number_of_time_each_philosophers_must_eat
		|| philo->number_of_time_each_philosophers_must_eat == -1)
	{
		if (philo->dead == 1)
			return (NULL);
		get_fork(philo, philo->t_start);
		if (philo->dead == 1)
			return (NULL);
		eat(philo, philo->t_start);
		++ntime_eat;
		if (philo->dead == 1)
			return (NULL);
		release_fork(philo);
		if (philo->dead == 1)
			return (NULL);
		if (psleep(philo, philo->t_start) == 1)
			return (NULL);
	}
	philo->eat = 1;
	return (NULL);
}
