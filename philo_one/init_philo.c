/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:47:21 by velovo            #+#    #+#             */
/*   Updated: 2020/05/26 15:35:48 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

int		check_for_error(t_philo *philo)
{
	if (philo->time_to_die < 50000 || philo->time_to_die > 20000000)
	{
		write(2, "Error : value out of range for time to die\n", 25);
		return (1);
	}
	if (philo->time_to_sleep < 0 || philo->time_to_sleep > 20000000)
	{
		write(2, "Error : value out of range for time to sleep\n", 25);
		return (1);
	}
	if (philo->time_to_eat < 0 || philo->time_to_eat > 20000000)
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
	if (argc < 5 && argc >= 7)
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
