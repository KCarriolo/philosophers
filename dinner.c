
#include "philo.h"

void	*routine(void *ptr)
{
	t_philo		*philo;

	philo = (t_philo *)ptr;
	if (!philo)
		return (NULL);
	lastmeal_update(philo);
	while (1)
	{
		if (is_thinking(philo) || is_eating(philo) || is_sleeping(philo))
			break ;
	}
	return (NULL);
}

int	plus_meal(t_philo *philo)
{
	if (!philo->eats_needed)
		return (0);
	pthread_mutex_lock(&philo->times_eaten_mtx[philo->my_index]);
	philo->times_eaten[philo->my_index]++;
	pthread_mutex_unlock(&philo->times_eaten_mtx[philo->my_index]);
	return (0);
}

void	lastmeal_update(t_philo *philo)
{
	pthread_mutex_lock(&philo->last_meal_mtx[philo->my_index]);
	philo->last_meal[philo->my_index] = catch_time(1);
	pthread_mutex_unlock(&philo->last_meal_mtx[philo->my_index]);
	return ;
}

int	is_dead(t_philo	*philo)
{
	pthread_mutex_lock(philo->dead_phil_mtx);
	if (*philo->dead_phil)
	{
		pthread_mutex_unlock(philo->dead_phil_mtx);
		return (1);
	}
	pthread_mutex_unlock(philo->dead_phil_mtx);
	return (0);
}
