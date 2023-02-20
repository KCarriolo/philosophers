
#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <limits.h>

typedef struct s_philo
{
	int					philo_count;
	int					philo_who;
	int					my_index;
	int					is_even;
	int					prev_f;
	int					next_f;
	int					eats_needed;
	int					time_to_eat;
	int					time_to_sleep;
	int					*times_eaten;
	pthread_mutex_t		*times_eaten_mtx;
	int					*forks;
	pthread_mutex_t		*forks_mtx;
	long unsigned int	*last_meal;
	pthread_mutex_t		*last_meal_mtx;
	int					*dead_phil;
	pthread_mutex_t		*dead_phil_mtx;
}	t_philo;

typedef struct s_proginfo
{
	int					philo_count;
	long unsigned		time_to_die;
	int					eats_needed;
	pthread_t			*thread_id;
	t_philo				**phil_vector;
	int					*times_eaten;
	pthread_mutex_t		*times_eaten_mtx;
	int					*forks;
	pthread_mutex_t		*forks_mtx;
	long unsigned int	*last_meal;
	pthread_mutex_t		*last_meal_mtx;
	int					*dead_phil;
	pthread_mutex_t		*dead_phil_mtx;
	pthread_t			reaper;
}	t_proginfo;

void		*ph_calloc(int size, int bytes);

long int	ph_atol(char *str);

long int	catch_time(int i);

int			intmax_validation(char **str);

int			ph_isdigit(int c);

int			fail_validation(char **str, int args);

int			if_in_range(int ac, char **str);

int			if_number(int ac, char **str);

void		initialize_mutex_struct_thread(t_proginfo *control, char **str);

void		create_control(t_proginfo *control, char **str, int if_times_eat);

t_philo		*create_thread_struct(t_proginfo *control, int i, char **str);

void		*routine(void *ptr);

int			is_thinking(t_philo *philo);

int			is_eating(t_philo *philo);

int			is_sleeping(t_philo *philo);

int			take_forks(t_philo *philo);

void		return_forks(t_philo *philo);

int			plus_meal(t_philo *philo);

void		lastmeal_update(t_philo *philo);

int			is_dead(t_philo	*philo);

int			smart_sleep(t_philo *philo, long unsigned int usec);

int			trylock_fork(t_philo *philo, int n_fork);

void		ph_unlock_fork(t_philo *philo, int n_fork);

int			even_philo_fork_take(t_philo *philo);

int			odd_philo_fork_take(t_philo *philo);

void		*reaper(void *ptr);

int			dead_phil(t_proginfo *control);

int			check_eaten_times(t_proginfo *control);

int			check_philo_death(t_proginfo *control, int i);

void		free_all(t_proginfo *control);

void		kill_mutexes(t_proginfo	*control);

void		exit_func(t_proginfo *control);

#endif

