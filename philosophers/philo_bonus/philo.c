#include "philo.h"

ssize_t	ft_get_ms(struct timeval time)
{
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

void	ft_print_msg(t_config *cnf, char *msg, ssize_t flag)
{
	struct timeval	cur_time;
	ssize_t			res_time;

	sem_wait(cnf->sem_msg);
	if (cnf->philo->check_life == 1)
	{
		gettimeofday(&cur_time, NULL);
		res_time = ft_get_ms(cur_time) - cnf->data->begin_time;
		printf("%zd\t%ld\t%s\n", res_time, cnf->philo->idx, msg);
	}
	if (flag == 1)
		sem_post(cnf->sem_msg);
}

static void	ft_eating(t_config *cnf)
{
	struct timeval	begin_time;
	struct timeval	cur_time;
	ssize_t			res_time;

	sem_wait(cnf->sem_fork);
	ft_print_msg(cnf, TAKE_FORK, 1);
	sem_wait(cnf->sem_fork);
	ft_print_msg(cnf, TAKE_FORK, 1);
	ft_print_msg(cnf, EATING, 1);
	res_time = 0;
	gettimeofday(&begin_time, NULL);
	while (cnf->philo->check_life == 1 && res_time < cnf->data->time_to_eat)
	{
		gettimeofday(&cur_time, NULL);
		res_time = ft_get_ms(cur_time) - ft_get_ms(begin_time);
		if (res_time < cnf->data->time_to_eat)
			usleep(500);
	}
	gettimeofday(&cur_time, NULL);
	cnf->philo->time_last_to_eat = ft_get_ms(cur_time);
	cnf->philo->count_of_times_eat += 1;
	sem_post(cnf->sem_fork);
	sem_post(cnf->sem_fork);
}

static void	ft_sleep(t_config *cnf)
{
	struct timeval	begin_time;
	struct timeval	cur_time;
	ssize_t			res_time;

	ft_print_msg(cnf, SLEEPING, 1);
	res_time = 0;
	gettimeofday(&begin_time, NULL);
	while (cnf->philo->check_life == 1 && res_time < cnf->data->time_to_sleep)
	{
		gettimeofday(&cur_time, NULL);
		res_time = ft_get_ms(cur_time) - ft_get_ms(begin_time);
		if (res_time < cnf->data->time_to_sleep)
			usleep(500);
	}
}

void	*ft_life(void *av)
{
	t_config	*cnf;

	cnf = av;
	if (cnf->philo->idx % 2 == 0)
		usleep(cnf->data->time_to_eat * 1000);
	while (cnf->philo->check_life == 1)
	{
		ft_eating(cnf);
		ft_sleep(cnf);
		ft_print_msg(cnf, THINKING, 1);
	}
	return (NULL);
}
