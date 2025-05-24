#include "philo.h"

t_bool	fk_take(t_philo *philo, t_fork *fork)
{
	t_bool is_available;

	pthread_mutex_lock(&fork->mutex);
	is_available = fork->is_available;
	fork->is_available = FALSE;
	pthread_mutex_unlock(&fork->mutex);
	if (is_available)
		print_action(taking, philo);
	return (is_available);
}

void	fk_put(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_available = TRUE;
	pthread_mutex_unlock(&fork->mutex);
}
