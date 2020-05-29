/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: velovo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 19:56:53 by velovo            #+#    #+#             */
/*   Updated: 2020/05/28 14:27:50 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

t_timeval	diff_time(t_timeval t1, t_timeval t2)
{
	unsigned long	time1;
	unsigned long	time2;
	t_timeval		ret;

	time1 = t1.tv_sec * 1000000 + t1.tv_usec;
	time2 = t2.tv_sec * 1000000 + t2.tv_usec;
	time2 -= time1;
	ret.tv_sec = time2 / 1000000;
	ret.tv_usec = (int)time2 - ret.tv_sec * 1000000;
	return (ret);
}

char		*join(char *s1, char *s2)
{
	int		i;
	int		n;
	char	*r;

	if (ft_strlen(s1) + ft_strlen(s2) == 0)
		return (NULL);
	if (!(r = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1))))
		return (NULL);
	i = 0;
	n = 0;
	while (s1 != NULL && s1[i])
	{
		r[i] = s1[i];
		i++;
	}
	while (s2 != NULL && s2[n])
	{
		r[i + n] = s2[n];
		n++;
	}
	r[i + n] = 0;
	return (r);
}

void		end_display(t_dish disp, int philo, char *msg)
{
	disp.tmp = disp.str;
	disp.toi = ft_itoa(philo);
	disp.str = join(disp.str, disp.toi);
	free(disp.toi);
	free(disp.tmp);
	disp.tmp = disp.str;
	disp.str = join(disp.str, " ");
	free(disp.tmp);
	disp.tmp = disp.str;
	disp.str = join(disp.str, msg);
	free(disp.tmp);
	disp.tmp = disp.str;
	disp.str = join(disp.str, "\n");
	free(disp.tmp);
	write(1, disp.str, ft_strlen(disp.str));
	free(disp.str);
}

void		display(t_timeval t_start, int philo, char *msg)
{
	t_timeval	t_time;
	t_dish		disp;
	int			i;
	int			time_ms;

	i = 0;
	gettimeofday(&t_time, NULL);
	t_time = diff_time(t_start, t_time);
	time_ms = t_time.tv_sec * 1000 + t_time.tv_usec / 1000;
	disp.toi = ft_itoa(time_ms);
	disp.str = NULL;
	while (i + ft_strlen(disp.toi) < 5)
	{
		disp.tmp = disp.str;
		disp.str = join(disp.str, "0");
		if (disp.str)
			free(disp.tmp);
		i++;
	}
	disp.tmp = disp.str;
	disp.str = join(disp.str, disp.toi);
	free(disp.tmp);
	disp.str = join(disp.str, " ");
	free(disp.toi);
	end_display(disp, philo, msg);
}