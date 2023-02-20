
#include "philo.h"

void	exit_func(t_proginfo *control)
{
	free_all(control);
	return ;
}

void	free_all(t_proginfo *control)
{
	int		i;

	i = 0;
	free(control->last_meal_mtx);
	free(control->last_meal);
	while (i < control->philo_count)
	{
		if (control->phil_vector[i])
			free(control->phil_vector[i]);
		i++;
	}
	free(control->phil_vector);
	free(control->thread_id);
	free(control->times_eaten);
	free(control->times_eaten_mtx);
	free(control->forks);
	free(control->forks_mtx);
	free(control->dead_phil);
	free(control->dead_phil_mtx);
	return ;
}
