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

void	ft_kill_processes(t_config *cnf)
{
	ssize_t	i;
	ssize_t	flag;
	int		status;

	i = -1;
	flag = 1;
	while (cnf->data != NULL && flag == 1 && ++i < cnf->data->nbr_of_philo)
	{
		waitpid(-1, &status, 0);
		if (status != 0)
		{
			i = 0;
			while (i < cnf->data->nbr_of_philo)
				kill(cnf->pid[i++], SIGKILL);
			flag = 0;
		}
	}
}

void	ft_free(t_config *cnf, ssize_t flag)
{
	if (cnf != NULL)
	{
		if (flag == 1)
		{
			ft_kill_processes(cnf);
			sem_close(cnf->sem_fork);
			sem_unlink("sem_fork");
			sem_close(cnf->sem_msg);
			sem_unlink("sem_msg");
		}
		else if (flag == 2)
		{
			sem_close(cnf->sem_fork);
			sem_unlink("sem_fork");
			sem_close(cnf->sem_msg);
			sem_unlink("sem_msg");
		}
		if (cnf->data != NULL)
			free(cnf->data);
		if (cnf->philo != NULL)
			free(cnf->philo);
		if (cnf->pid != NULL)
			free(cnf->pid);
		free(cnf);
	}
}

void	ft_print_error(t_config *cnf, char *desc, char *name)
{
	write(2, "pipex: ", 7);
	write(2, desc, ft_strlen(desc));
	write(2, ": ", 2);
	write(2, name, ft_strlen(name));
	write(2, "\n", 1);
	ft_free(cnf, 1);
	exit(1);
}
