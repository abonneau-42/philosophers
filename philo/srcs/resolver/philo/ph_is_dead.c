#include "philo.h"

t_bool	ph_is_dead(t_philo *philo)
{
	__uint64_t	time;

	time = ft_get_time();
	if (time - philo->last_time_eaten > philo->data->args->time_to_die)
	{
		print_action(dead, philo);
		return (TRUE);
	}
	return (FALSE);
}