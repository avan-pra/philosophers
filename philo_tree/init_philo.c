#include "philo_tree.h"

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

int        fill_and_error(t_philo *philo, char **argv, int argc)
{
    if (argc < 5 || argc >= 7)
    { 
        write(2, "Error while parsing argv\n", 25);
        return (1);
    }
    else
        philo->number_of_time_each_philosophers_must_eat = (argc == 6) ? ft_atoi(argv[5]) : -1;
    philo->number_of_philosopher = ft_atoi(argv[1]);
    philo->time_to_die = ft_atoi(argv[2]) * 1000;
    philo->time_to_eat = ft_atoi(argv[3]) * 1000;
    philo->time_to_sleep = ft_atoi(argv[4]) * 1000;
    if (philo->time_to_die < 50000 || philo->time_to_die >= 10000000)
    { 
        write(2, "Error : value out of range for time to die\n", 42);
        return (1);
    }
    if (philo->time_to_sleep < 0 || philo->time_to_sleep >= 10000000)
    { 
        write(2, "Error : value out of range for time to sleep\n", 42);
        return (1);
    }
    if (philo->time_to_eat < 0 || philo->time_to_eat >= 10000000)
    { 
        write(2, "Error : value out of range for time to eat\n", 42);
        return (1);
    }
    if (philo->number_of_philosopher < 0 || philo->number_of_philosopher > 10000)
    { 
        write(2, "Error : value out of range for number of philosophers\n", 25);
        return (1);
    }
    return (0);
}

char    *ft_itoa_next(unsigned long long dec,
    unsigned long long nb, int size)
{
    int             test;
    char    *res;

    test = 0;
    res = malloc(size * sizeof(char));
    while (test < size)
    {
        if (nb >= 10)
        {
            dec = dec / 10;
            res[test] = nb / dec + '0';
            nb -= nb / dec * dec;
        }
        else
            res[test] = nb % 10 + '0';
        test++;
    }
    res[test] = '\0';
    return (res);
}

char    *ft_itoa(unsigned long long nb)
{
    unsigned long long      test;
    unsigned int            size;
    unsigned long long      dec;

    dec = 1;
    size = 1;
    test = nb;
    while (test / 10 != 0)
    {
        size++;
        test = test / 10;
    }
    test = 0;
    while (test++ < size)
        dec *= 10;
    return (ft_itoa_next(dec, nb, size));
}

int ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
