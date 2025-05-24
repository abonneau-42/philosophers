#include "philo.h"

__uint64_t	get_time_to_wait(__uint64_t duration, t_philo *philo)
{
	__uint64_t	current_time;
	__uint64_t	end_default;
	__uint64_t	end_dead;
	__uint64_t	end_no_time;

	current_time = get_time();
	end_default = current_time + duration;
	end_dead = current_time + philo->data->args->time_to_die;
	end_no_time = philo->last_time_eaten + philo->data->args->time_to_die;
	if (end_dead < end_default && end_dead <= end_no_time)
		return (end_dead + 1);
	if (end_no_time < end_default && end_no_time <= end_dead)
		return (end_no_time + 1);
	return (end_default);
}

inline void	ph_sleep(__uint64_t duration, t_philo *philo)
{
	__uint64_t	time;

	time = get_time_to_wait(duration, philo);
	while (get_time() < time)
		usleep(250);
	ph_is_dead(philo);
}