
#include "philo.h"

int	main(int argc, char **argv)
{
	int			i;
	t_proginfo	*control;

	control = &(t_proginfo){0};
	i = 0;
	if (fail_validation(argv, (argc - 1)))
		return (0);
	if (argc == 5)
		create_control(control, argv, 0);
	else
		create_control(control, argv, 1);
	initialize_mutex_struct_thread(control, argv);
	pthread_join(control->reaper, NULL);
	while (i < control->philo_count)
	{
		pthread_join(control->thread_id[i], NULL);
		i++;
	}
	exit_func(control);
	return (0);
}
