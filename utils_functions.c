
#include "philo.h"

void	*ph_calloc(int size, int bytes)
{
	void	*ptr;

	if (size <= 0 || bytes <= 0)
		return (NULL);
	ptr = malloc(size * bytes);
	if (!ptr)
		return (NULL);
	ptr = memset(ptr, 0, (size * bytes));
	if (!ptr)
		return (NULL);
	return (ptr);
}

long int	catch_time(int i)
{
	long int		current_time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	current_time = ((tv.tv_sec * 1000000) + tv.tv_usec);
	return (current_time / i);
}

int	trylock_fork(t_philo *philo, int n_fork)
{
	if (!philo || n_fork < 0)
		return (0);
	pthread_mutex_lock(&philo->forks_mtx[n_fork]);
	if (!philo->forks[n_fork])
	{
		philo->forks[n_fork] = 1;
		pthread_mutex_unlock(&philo->forks_mtx[n_fork]);
		printf("%ld %d has taken a fork\n",
			catch_time(1000), philo->philo_who);
		return (1);
	}
	pthread_mutex_unlock(&philo->forks_mtx[n_fork]);
	return (0);
}

void	ph_unlock_fork(t_philo *philo, int n_fork)
{
	if (!philo || n_fork < 0)
		return ;
	pthread_mutex_lock(&philo->forks_mtx[n_fork]);
	philo->forks[n_fork] = 0;
	pthread_mutex_unlock(&philo->forks_mtx[n_fork]);
	return ;
}

int		smart_sleep(t_philo *philo, long unsigned int usec)
{
	long int	end;

	end = catch_time(1) + usec;
	while (end > catch_time(1))
	{
		usleep(100);
		if (is_dead(philo))
			return (1);
	}
	return (0);
}
