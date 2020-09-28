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
}

void	init_mutex(pthread_mutex_t *mutex, int nbr, pthread_mutex_t mort)
{
	int i;

	i = 0;
	while (i < nbr)
	{
		pthread_mutex_init(&mutex[i], NULL);
		++i;
	}
}

int		check_status(t_philo philo, t_creat info)
{
	pthread_create(&info.win, NULL, &winner, &philo);
	pthread_create(&info.lose, NULL, &loser, &philo);
	while (1)
	{
		if (philo.dead == 1)
		{
			usleep(1000);
			printf("End of simulation : one of the philosophers died\n");
			return (1);
		}
		else if (philo.dead == 2)
		{
			usleep(1000);
			printf("End of simulation : philosophers ate enough times\n");
			return (0);
		}
		usleep(1000);
	}
}

int		create_start_philo(int nbr, t_philo philo)
{
	t_philo			arr[nbr];
	pthread_t		th[nbr];
	pthread_mutex_t	mutext[philo.number_of_philosopher];
	t_creat			info;

	init_mutex(mutext, philo.number_of_philosopher, info.mort);
	pthread_mutex_init(&info.mort, NULL);
	pthread_mutex_lock(&info.mort);
	gettimeofday(&philo.t_start, NULL);
	philo.dead = 0;
	info.j = 0;
	while (info.j < philo.number_of_philosopher)
	{
		copy_struct(&arr[info.j], philo, info.j);
		arr[info.j].die = &info.mort;
		arr[info.j].mutext1 = &mutext[info.j];
		arr[info.j].mutext2 = (info.j + 1 == philo.number_of_philosopher) ?
			&mutext[0] : &mutext[info.j + 1];
		pthread_create(&th[info.j], NULL, &ft_philosopher, &arr[info.j]);
		usleep(100);
		++info.j;
	}
	philo.th = (pthread_t*)&th;
	philo.die = &info.mort;
	return (check_status(philo, info));
}

int		main(int argc, char **argv)
{
	t_philo	philo;
	int		j;

	srand(time(0));
	if (fill_and_error(&philo, argv, argc) == 1)
		return (1);
	return (create_start_philo(philo.number_of_philosopher, philo));
}
