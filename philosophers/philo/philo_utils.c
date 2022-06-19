#include "philo.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

int	ft_atoi(const char *nptr)
{
	int		i;
	int		sign;
	long	num;
	int		len;

	i = 0;
	sign = 1;
	len = ft_strlen(nptr);
	if (nptr[i] == '-')
	{
		sign = -sign;
		i++;
	}
	num = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		num = (num * 10) + (nptr[i] - '0');
		if ((sign == 1 && num > 2147483647) || (sign == -1 && num > 2147483648))
			return (-1);
		++i;
	}
	if (len != i)
		return (-1);
	else
		return (sign * num);
}

int	ft_print_error(t_config *cnf, char *desc, char *name)
{
	write(2, "Philo: ", 7);
	write(2, desc, ft_strlen(desc));
	write(2, ": ", 2);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
	ft_free(cnf);
	return (1);
}

void	ft_free(t_config *cnf)
{
	ssize_t	i;

	if (cnf != NULL)
	{
		if (cnf->philo != NULL)
		{
			i = 0;
			while (i < cnf->data->nbr_of_philo)
				free(cnf->philo[i++].right_fork);
			free(cnf->philo);
		}
		if (cnf->data != NULL)
			free(cnf->data);
		free(cnf);
	}
}

ssize_t	ft_get_ms(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}
