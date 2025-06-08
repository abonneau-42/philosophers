#include "philo.h"

t_bool	ph_is_dead(t_philo *philo)
{
	__uint64_t	time;

	time = get_time();
	if (time - philo->lts_eat > philo->data->args->lifetime)
	{
		print_action(dead, philo);
		return (TRUE);
	}
	return (FALSE);
}
