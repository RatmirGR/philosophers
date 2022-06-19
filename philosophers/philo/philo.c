#include "philo.h"

size_t	ft_observer(t_philo *phil)
{
	ssize_t			i;
	struct timeval	cur_time;
	ssize_t			time;

	while (phil->data->check_life == 1)
	{
		phil->data->count_eat = 0;
		i = -1;
		while ((++i) < phil->data->nbr_of_philo && phil->data->check_life == 1)
		{
			gettimeofday(&cur_time, NULL);
			time = ft_get_ms(cur_time) - ft_get_ms(phil[i].time_last_to_eat_tv);
			if (time > phil->data->time_to_die)
			{
				ft_print_msg(&phil[i], "died");
				return (1);
			}
			else if (phil->data->nbr_of_times_eat != 0
				&& phil->data->nbr_of_times_eat <= phil[i].count_of_times_eat)
				phil->data->count_eat++;
		}
		if (phil->data->count_eat >= phil->data->nbr_of_philo)
			phil->data->check_life = 0;
	}
	return (0);
}

void	ft_print_msg(t_philo *philo, char *msg)
{
	struct timeval	cur_time;
	ssize_t			res_time;

	pthread_mutex_lock(&philo->data->mutex_wrapper);
	if (philo->data->check_life == 1)
	{
		gettimeofday(&cur_time, NULL);
		res_time = ft_get_ms(cur_time) - ft_get_ms(philo->data->begin_time_tv);
		printf("%ld\t%ld\t%s\n", res_time, philo->idx, msg);
	}
	pthread_mutex_unlock(&philo->data->mutex_wrapper);
}

static void	ft_eating(t_philo *philo)
{
	struct timeval	begin_time;
	struct timeval	cur_time;
	ssize_t			res_time;

	pthread_mutex_lock(philo->left_fork);
	ft_print_msg(philo, TAKE_FORK);
	pthread_mutex_lock(philo->right_fork);
	ft_print_msg(philo, TAKE_FORK);
	ft_print_msg(philo, EATING);
	gettimeofday(&begin_time, NULL);
	res_time = 0;
	while (philo->data->check_life == 1 && res_time < philo->data->time_to_eat)
	{
		gettimeofday(&cur_time, NULL);
		res_time = ft_get_ms(cur_time) - ft_get_ms(begin_time);
		if (res_time < philo->data->time_to_eat)
			usleep(500);
	}
	philo->count_of_times_eat += 1;
	gettimeofday(&cur_time, NULL);
	philo->time_last_to_eat_tv = cur_time;
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_unlock(philo->left_fork);
}

static void	ft_sleep(t_philo *philo)
{
	struct timeval	begin_time;
	struct timeval	cur_time;
	ssize_t			restime;

	ft_print_msg(philo, SLEEPING);
	gettimeofday(&begin_time, NULL);
	restime = 0;
	while (philo->data->check_life == 1 && restime < philo->data->time_to_sleep)
	{
		gettimeofday(&cur_time, NULL);
		restime = ft_get_ms(cur_time) - ft_get_ms(begin_time);
		if (restime < philo->data->time_to_sleep)
			usleep(500);
	}
}

void	*ft_life(void *av)
{
	t_philo	*philo;

	philo = (t_philo *)av;
	if (philo->idx % 2 == 0)
		usleep(philo->data->time_to_eat * 1000);
	while (philo->data->check_life == 1)
	{
		ft_eating(philo);
		ft_sleep(philo);
		ft_print_msg(philo, THINKING);
	}
	return (NULL);
}
