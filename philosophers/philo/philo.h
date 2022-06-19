#ifndef PHILO_H
# define PHILO_H

# define INVALID_ARGS "Invalid number of arguments"
# define INVALID_ARG "Invalid argument"
# define ERROR_MEM "Memory allocation error"
# define TAKE_FORK "has taken a fork"
# define EATING "is eating"
# define THINKING "is thinking"
# define SLEEPING "is sleeping"

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	ssize_t			nbr_of_philo;
	ssize_t			time_to_die;
	ssize_t			time_to_eat;
	ssize_t			time_to_sleep;
	ssize_t			nbr_of_times_eat;
	ssize_t			check_life;
	struct timeval	begin_time_tv;
	pthread_mutex_t	mutex_wrapper;
	ssize_t			count_eat;
}					t_data;

typedef struct s_philo
{
	ssize_t			idx;
	pthread_t		tid;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	ssize_t			count_of_times_eat;
	t_data			*data;
	struct timeval	time_last_to_eat_tv;
}					t_philo;

typedef struct s_config
{
	t_philo	*philo;
	t_data	*data;
}			t_config;

size_t	ft_strlen(const char *s);
int		ft_print_error(t_config *cnf, char *desc, char *name);
int		ft_atoi(const char *nptr);
void	ft_free(t_config *cnf);
size_t	ft_simulation(t_config *cnf);
void	*ft_life(void *av);
size_t	ft_observer(t_philo *phil);
ssize_t	ft_get_ms(struct timeval time);
void	ft_print_msg(t_philo *philo, char *msg);

#endif