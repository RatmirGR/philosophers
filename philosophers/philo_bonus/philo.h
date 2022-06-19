#ifndef PHILO_H
# define PHILO_H

# define INVALID_ARGS "Invalid number of arguments"
# define INVALID_ARG "Invalid argument"
# define ERROR_SEM "Error in semaphore operation"
# define ERROR_MEM "Memory allocation error"
# define ERROR_FORK "Error fork"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_data
{
	ssize_t	nbr_of_philo;
	ssize_t	time_to_die;
	ssize_t	time_to_eat;
	ssize_t	time_to_sleep;
	ssize_t	nbr_of_times_eat;
	ssize_t	begin_time;
}			t_data;

typedef struct s_philo
{
	ssize_t	idx;
	ssize_t	count_of_times_eat;
	ssize_t	check_life;
	ssize_t	time_last_to_eat;
}			t_philo;

typedef struct s_config
{
	t_data	*data;
	t_philo	*philo;
	pid_t	*pid;
	sem_t	*sem_fork;
	sem_t	*sem_msg;
}			t_config;

size_t	ft_strlen(const char *s);
int		ft_atoi(const char *nptr);
void	ft_free(t_config *cnf, ssize_t flag);
void	ft_print_error(t_config *cnf, char *desc, char *name);

void	*ft_life(void *av);
void	*ft_observer(void *av);
ssize_t	ft_get_ms(struct timeval time);
void	ft_print_msg(t_config *cnf, char *msg, ssize_t flag);

#endif