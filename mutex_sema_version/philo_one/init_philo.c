/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/29 14:33:33 by avan-pra          #+#    #+#             */
/*   Updated: 2020/09/29 14:33:39 by avan-pra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_for_error(t_philo *philo)
{
	if (philo->time_to_die < 60000 || philo->time_to_die > 20000000)
	{
		write(2, "Error : value out of range for time to die\n", 25);
		return (1);
	}
	if (philo->time_to_sleep < 60000 || philo->time_to_sleep > 20000000)
	{
		write(2, "Error : value out of range for time to sleep\n", 25);
		return (1);
	}
	if (philo->time_to_eat < 60000 || philo->time_to_eat > 20000000)
	{
		write(2, "Error : value out of range for time to eat\n", 25);
		return (1);
	}
	if (philo->number_of_philosopher < 0
		|| philo->number_of_philosopher > 10000)
	{
		write(2, "Error : value out of range for number of philosophers\n", 25);
		return (1);
	}
	return (0);
}

int		fill_and_error(t_philo *philo, char **argv, int argc)
{
	if (argc < 5 || argc >= 7)
	{
		write(2, "Error while parsing argv\n", 25);
		return (1);
	}
	else
		philo->number_of_time_each_philosophers_must_eat = (argc == 6) ?
		ft_atoi(argv[5]) :
		-1;
	philo->number_of_philosopher = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	return (check_for_error(philo));
}
