
#include "philo.h"

int	is_thinking(t_philo *philo)
{
	printf("%ld %d is thinking\n", catch_time(1000), philo->philo_who);
	return (0);
}

int	is_eating(t_philo *philo)
{
	if (take_forks(philo))
		return (1);
	lastmeal_update(philo);
	printf("%ld %d is eating\n", catch_time(1000), philo->philo_who);
	if(smart_sleep(philo, philo->time_to_eat))
		return (1);
	return_forks(philo);
	plus_meal(philo);
	return (0);
}

int	is_sleeping(t_philo *philo)
{
	printf("%ld %d is sleeping\n", catch_time(1000), philo->philo_who);
	if(smart_sleep(philo, philo->time_to_sleep))
		return (1);
	return (0);
}
