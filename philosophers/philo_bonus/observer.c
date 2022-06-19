#include "philo.h"

void	*ft_observer(void *av)
{
	t_config		*cnf;
	struct timeval	cur_time;
	ssize_t			time;

	cnf = av;
	while (cnf->philo->check_life == 1)
	{
		gettimeofday(&cur_time, NULL);
		time = ft_get_ms(cur_time) - cnf->philo->time_last_to_eat;
		if (time > cnf->data->time_to_die)
		{
			ft_print_msg(cnf, "died", 0);
			if (cnf->data->nbr_of_philo == 1)
				ft_free(cnf, 0);
			else
				ft_free(cnf, 2);
			exit(1);
		}
		else if (cnf->data->nbr_of_times_eat != 0
			&& cnf->data->nbr_of_times_eat <= cnf->philo->count_of_times_eat)
			exit(0);
	}
	return (NULL);
}
