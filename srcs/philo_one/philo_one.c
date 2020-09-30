/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/26 15:34:39 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	copy_struct(t_philo *paste, t_philo copy, int nbr)
{
	paste->number_of_philosopher = copy.number_of_philosopher;
	paste->number_of_time_each_philosophers_must_eat =
		copy.number_of_time_each_philosophers_must_eat;
	paste->time_to_die = copy.time_to_die;
	paste->time_to_eat = copy.time_to_eat;
	paste->time_to_sleep = copy.time_to_sleep;
	paste->t_start = copy.t_start;
	paste->dead = 0;
	paste->number = nbr;
	paste->output = copy.output;
}

int		check_status(t_philo *philo, t_creat info)
{
	pthread_create(&info.win, NULL, &winner, philo);
	pthread_create(&info.lose, NULL, &loser, philo);
	while (1)
	{
		if (philo->dead == 1)
			return (1);
		else if (philo->dead == 2)
		{
			write(1, "End of simulation : philosophers ate enough times\n", 50);
			return (0);
		}
	}
}

void	setup_philo_launch
	(t_philo *philo, pthread_mutex_t *output, t_creat *info)
{
	pthread_mutex_init(output, NULL);
	pthread_mutex_init(&info->mort, NULL);
	pthread_mutex_lock(&info->mort);
	gettimeofday(&philo->t_start, NULL);
	philo->dead = 0;
	philo->output = output;
	info->j = 0;
}

int		create_start_philo(int nbr, t_philo philo)
{
	t_philo			arr[nbr];
	pthread_t		th[nbr];
	pthread_mutex_t output;
	pthread_mutex_t	mutext[philo.number_of_philosopher];
	t_creat			info;

	init_mutex(mutext, philo.number_of_philosopher);
	setup_philo_launch(&philo, &output, &info);
	while (info.j < philo.number_of_philosopher)
	{
		copy_struct(&arr[info.j], philo, info.j);
		arr[info.j].die = &info.mort;
		arr[info.j].mutext1 = &mutext[info.j];
		arr[info.j].mutext2 = (info.j + 1 == philo.number_of_philosopher) ?
			&mutext[0] : &mutext[info.j + 1];
		pthread_create(&th[info.j], NULL, &ft_philosopher, &arr[info.j]);
		usleep(40);
		++info.j;
	}
	philo.th = (pthread_t*)&th;
	philo.die = &info.mort;
	return (check_status(&philo, info));
}

int		main(int argc, char **argv)
{
	t_philo	philo;

	srand(time(0));
	if (fill_and_error(&philo, argv, argc) == 1)
		return (1);
	return (create_start_philo(philo.number_of_philosopher, philo));
}
