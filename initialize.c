
#include "philo.h"

void	create_control(t_proginfo *control, char **str, int if_times_eat)
{
	control->philo_count = ph_atol(str[1]);
	control->time_to_die = ph_atol(str[2]) * 1000;
	control->last_meal_mtx = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->philo_count + 1);
	control->last_meal = ph_calloc(sizeof(long int), (control->philo_count + 1));
	control->phil_vector = ph_calloc(sizeof(t_philo *), control->philo_count + 1);
	control->thread_id = (pthread_t *)
		ph_calloc(sizeof(pthread_t *), control->philo_count + 1);
	control->dead_phil_mtx = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), 1);
	control->dead_phil = (int *)ph_calloc(sizeof(int), 1);
	control->forks = (int *)ph_calloc(sizeof(int), ph_atol(str[1]));
	control->forks_mtx = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->philo_count + 1);
	control->times_eaten = (int *)ph_calloc(sizeof(int), control->philo_count + 1);
	control->times_eaten_mtx = (pthread_mutex_t *)
		ph_calloc(sizeof(pthread_mutex_t), control->philo_count + 1);
	if (if_times_eat)
		control->eats_needed = ph_atol(str[5]);
	else
		control->eats_needed = 0;
	return ;
}

t_philo	*create_thread_struct(t_proginfo *control, int i, char **str)
{
	t_philo	*philo;

	philo = ph_calloc(sizeof(t_philo), 1);
	philo->philo_count = control->philo_count;
	philo->time_to_eat = ph_atol(str[3]) * 1000;
	philo->time_to_sleep = ph_atol(str[4]) * 1000;
	philo->philo_who = i;
	if (philo->philo_who % 2)
		philo->is_even = 1;
	philo->my_index = i - 1;
	philo->forks = control->forks;
	philo->forks_mtx = control->forks_mtx;
	philo->last_meal = control->last_meal;
	philo->last_meal_mtx = control->last_meal_mtx;
	philo->dead_phil = control->dead_phil;
	philo->dead_phil_mtx = control->dead_phil_mtx;
	philo->times_eaten = control->times_eaten;
	philo->times_eaten_mtx = control->times_eaten_mtx;
	philo->eats_needed = control->eats_needed;
	philo->prev_f = i - 1;
	philo->next_f = i;
	if (philo->next_f == control->philo_count)
		philo->next_f = 0;
	return (philo);
}

void	initialize_mutex_struct_thread(t_proginfo *control, char **str)
{
	int	i;

	i = -1;
	while (++i < control->philo_count)
	{
		pthread_mutex_init(&control->times_eaten_mtx[i], NULL);
		pthread_mutex_init(&control->forks_mtx[i], NULL);
		pthread_mutex_init(&control->last_meal_mtx[i], NULL);
	}
	pthread_mutex_init(control->dead_phil_mtx, NULL);
	i = -1;
	while (++i < control->philo_count)
		control->phil_vector[i] = create_thread_struct(control, i + 1, str);
	i = -1;
	while (++i < control->philo_count)
	{
		pthread_create(&control->thread_id[i], NULL,
			&routine, control->phil_vector[i]);
	}
	pthread_create(&control->reaper, NULL, &reaper, control);
	return ;
}
