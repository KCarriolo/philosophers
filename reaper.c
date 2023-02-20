
#include "philo.h"

void	*reaper(void *ptr)
{
	int			i;
	t_proginfo	*control;

	control = (t_proginfo *)ptr;
	i = 0;
	while (1)
	{
		if (i == control->philo_count)
			i = 0;
		if (check_philo_death(control, i) || check_eaten_times(control))
			return (NULL);
		i++;
	}
	return (NULL);
}

int	check_philo_death(t_proginfo *control, int i)
{
	pthread_mutex_lock(&control->last_meal_mtx[i]);
	if (control->last_meal[i] && ((catch_time(1) - control->last_meal[i]) > control->time_to_die))
	{
		pthread_mutex_lock(control->dead_phil_mtx);
		*control->dead_phil = 1;
		pthread_mutex_unlock(control->dead_phil_mtx);
		printf("%ld %d has died\n", catch_time(1000), i + 1);
		pthread_mutex_unlock(&control->last_meal_mtx[i]);
		return (1);
	}
	pthread_mutex_unlock(&control->last_meal_mtx[i]);
	return (0);
}

int	check_eaten_times(t_proginfo *control)
{
	int	i;

	i = 0;
	if (!control->eats_needed)
		return (0);
	while (i < control->philo_count)
	{
		pthread_mutex_lock(&control->times_eaten_mtx[i]);
		if (control->times_eaten[i] < control->eats_needed)
		{
			pthread_mutex_unlock(&control->times_eaten_mtx[i]);
			return (0);
		}
		pthread_mutex_unlock(&control->times_eaten_mtx[i]);
		i++;
	}
	pthread_mutex_lock(control->dead_phil_mtx);
	*control->dead_phil = 1;
	pthread_mutex_unlock(control->dead_phil_mtx);
	return (1);
}
