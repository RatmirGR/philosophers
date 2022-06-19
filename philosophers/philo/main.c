#include "philo.h"

size_t	ft_init_config(t_config **cnf)
{
	*cnf = NULL;
	*cnf = malloc(sizeof(t_config));
	if (*cnf == NULL)
		return (1);
	(*cnf)->philo = NULL;
	(*cnf)->data = NULL;
	(*cnf)->data = malloc(sizeof(t_data));
	if ((*cnf)->data == NULL)
		return (1);
	(*cnf)->data->nbr_of_philo = 0;
	(*cnf)->data->time_to_die = 0;
	(*cnf)->data->time_to_eat = 0;
	(*cnf)->data->time_to_sleep = 0;
	(*cnf)->data->nbr_of_times_eat = 0;
	(*cnf)->data->check_life = 1;
	pthread_mutex_init(&(*cnf)->data->mutex_wrapper, NULL);
	return (0);
}

size_t	ft_validate_args(t_config *cnf, int ac, char *av[])
{
	cnf->data->nbr_of_philo = ft_atoi(av[1]);
	cnf->data->time_to_die = ft_atoi(av[2]);
	cnf->data->time_to_eat = ft_atoi(av[3]);
	cnf->data->time_to_sleep = ft_atoi(av[4]);
	if (cnf->data->nbr_of_philo < 0 || cnf->data->time_to_die < 0
		|| cnf->data->time_to_eat < 0 || cnf->data->time_to_sleep < 0)
		return (1);
	if (ac == 6)
	{
		cnf->data->nbr_of_times_eat = ft_atoi(av[5]);
		if (cnf->data->nbr_of_times_eat <= 0)
			return (1);
	}
	return (0);
}

size_t	ft_init_philos(t_config *cnf)
{
	ssize_t			i;
	pthread_mutex_t	*fork;
	t_philo			*philo;

	philo = malloc(cnf->data->nbr_of_philo * sizeof(t_philo));
	if (philo == NULL)
		return (1);
	i = 0;
	while (i < cnf->data->nbr_of_philo)
	{
		philo[i].idx = i + 1;
		philo[i].tid = 0;
		philo[i].count_of_times_eat = 0;
		philo[i].data = cnf->data;
		fork = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(fork, NULL);
		if (i != 0)
			philo[i].left_fork = philo[i - 1].right_fork;
		philo[i].right_fork = fork;
		i++;
	}
	philo[0].left_fork = philo[cnf->data->nbr_of_philo - 1].right_fork;
	cnf->philo = philo;
	return (0);
}

size_t	ft_simulation(t_config *cnf)
{
	ssize_t			i;
	struct timeval	start_time;
	t_philo			*philo;

	philo = (t_philo *)cnf->philo;
	i = 0;
	gettimeofday(&start_time, NULL);
	cnf->data->begin_time_tv = start_time;
	while (i < cnf->data->nbr_of_philo)
	{
		gettimeofday(&start_time, NULL);
		philo[i].time_last_to_eat_tv = start_time;
		pthread_create(&philo[i].tid, NULL, &ft_life, &philo[i]);
		pthread_detach(philo[i++].tid);
	}
	ft_observer(philo);
	i = 0;
	while (i < cnf->data->nbr_of_philo)
		pthread_mutex_destroy(philo[i++].right_fork);
	pthread_mutex_destroy(&philo->data->mutex_wrapper);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_config	*cnf;

	if (argc != 5 && argc != 6)
		return (ft_print_error(NULL, INVALID_ARGS, "1"));
	if (ft_init_config(&cnf) == 1)
		return (ft_print_error(NULL, ERROR_MEM, "1"));
	if (ft_validate_args(cnf, argc, argv) == 1)
		return (ft_print_error(cnf, INVALID_ARG, "1"));
	if (ft_init_philos(cnf) == 1)
		return (ft_print_error(cnf, ERROR_MEM, "1"));
	ft_simulation(cnf);
	ft_free(cnf);
	return (0);
}
