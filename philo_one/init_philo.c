#include "phile_one.h"

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

int		fill_and_error(t_philo *philo, char **argv, int argc)
{
	if (argc < 5 || argc >= 7)
	{ 
		write(2, "error while parsing argv\n", 25);
		return (1);
	}
	else if (argc == 6)
		philo->number_of_time_each_philosophers_must_eat = ft_atoi(argv[5]);
	else
		philo->number_of_time_each_philosophers_must_eat = 0;
	philo->number_of_philosopher = ft_atoi(argv[1]);
	philo->time_to_die = ft_atoi(argv[2]) * 1000;
	philo->time_to_eat = ft_atoi(argv[3]) * 1000;
	philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
	return (0);
}
