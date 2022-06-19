#include "philo.h"

static void	ft_init_config(t_config **cnf)
{
	*cnf = NULL;
	*cnf = malloc(sizeof(t_config));
	if (*cnf == NULL)
		ft_print_error(NULL, ERROR_MEM, "1");
	(*cnf)->data = NULL;
	(*cnf)->data = malloc(sizeof(t_philo));
	if ((*cnf)->data == NULL)
		ft_print_error(NULL, ERROR_MEM, "1");
	(*cnf)->data->nbr_of_philo = 0;
	(*cnf)->data->time_to_die = 0;
	(*cnf)->data->time_to_eat = 0;
	(*cnf)->data->time_to_sleep = 0;
	(*cnf)->data->nbr_of_times_eat = 0;
	(*cnf)->philo = NULL;
	(*cnf)->philo = malloc(sizeof(t_philo));
	if ((*cnf)->philo == NULL)
		ft_print_error(NULL, ERROR_MEM, "1");
	(*cnf)->philo->count_of_times_eat = 0;
	(*cnf)->philo->check_life = 1;
	(*cnf)->pid = NULL;
	(*cnf)->sem_fork = NULL;
	(*cnf)->sem_msg = NULL;
}

static void	ft_validate_args(t_config *cnf, int ac, char *av[])
{
	cnf->data->nbr_of_philo = ft_atoi(av[1]);
	cnf->data->time_to_die = ft_atoi(av[2]);
	cnf->data->time_to_eat = ft_atoi(av[3]);
	cnf->data->time_to_sleep = ft_atoi(av[4]);
	if (cnf->data->nbr_of_philo < 0 || cnf->data->time_to_die < 0
		|| cnf->data->time_to_eat < 0 || cnf->data->time_to_sleep < 0)
		ft_print_error(cnf, INVALID_ARG, "1");
	if (ac == 6)
	{
		cnf->data->nbr_of_times_eat = ft_atoi(av[5]);
		if (cnf->data->nbr_of_times_eat <= 0)
			ft_print_error(cnf, INVALID_ARG, "1");
	}
}

static void	ft_init_semaphore(t_config *cnf)
{
	t_data	*data;

	data = cnf->data;
	sem_unlink("sem_fork");
	sem_unlink("sem_msg");
	cnf->sem_fork = sem_open("sem_fork", O_CREAT, 0644, data->nbr_of_philo);
	if (cnf->sem_fork == SEM_FAILED)
		ft_print_error(cnf, ERROR_SEM, "1");
	cnf->sem_msg = sem_open("sem_msg", O_CREAT, 0644, 1);
	if (cnf->sem_msg == SEM_FAILED)
		ft_print_error(cnf, ERROR_SEM, "1");
}

static void	ft_simulation(t_config *cnf)
{
	ssize_t			i;
	pthread_t		tid_obs;
	struct timeval	start_time;

	cnf->pid = malloc(sizeof(pid_t) * cnf->data->nbr_of_philo);
	if (cnf->pid == NULL)
		ft_print_error(cnf, ERROR_MEM, "1");
	i = -1;
	gettimeofday(&start_time, NULL);
	cnf->data->begin_time = ft_get_ms(start_time);
	while ((++i) < cnf->data->nbr_of_philo)
	{
		cnf->pid[i] = fork();
		if (cnf->pid[i] < 0)
			ft_print_error(cnf, ERROR_FORK, "1");
		if (cnf->pid[i] == 0)
		{
			cnf->philo->idx = i + 1;
			gettimeofday(&start_time, NULL);
			cnf->philo->time_last_to_eat = ft_get_ms(start_time);
			pthread_create(&tid_obs, NULL, &ft_observer, cnf);
			ft_life(cnf);
			pthread_join(tid_obs, NULL);
		}
	}
}

int	main(int argc, char *argv[])
{
	t_config	*cnf;

	if (argc != 5 && argc != 6)
		ft_print_error(NULL, INVALID_ARGS, "1");
	ft_init_config(&cnf);
	ft_validate_args(cnf, argc, argv);
	ft_init_semaphore(cnf);
	ft_simulation(cnf);
	ft_free(cnf, 1);
	return (0);
}
