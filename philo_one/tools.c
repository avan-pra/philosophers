/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-pra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 13:22:36 by avan-pra          #+#    #+#             */
/*   Updated: 2020/05/26 15:35:36 by raimbaul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

long			ft_longueur(long n)
{
	long		l;

	if (n <= 0)
		l = 1;
	else
		l = 0;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

int		ft_atoi(const char *str)
{
	int				i;
	int				ret;
	unsigned long	result;

	i = 0;
	ret = 1;
	if (!str)
		return (0);
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			ret = -1;
		i++;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return ((int)result * ret);
}

char			*ft_itoa(long nb)
{
	long				sign;
	long				len;
	char				*str;

	sign = (nb < 0 ? 1 : 0);
	str = NULL;
	len = ft_longueur(nb);
	if (sign == 1)
		nb = -nb;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
