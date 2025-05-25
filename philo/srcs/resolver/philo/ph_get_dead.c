#include "philo.h"

t_bool	ph_get_dead(t_common_data *data)
{
	t_bool	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->philo_is_dead;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	ph_stop_all(t_common_data *data)
{
	pthread_mutex_lock(&data->death_mutex);
	data->philo_is_dead = TRUE;
	pthread_mutex_unlock(&data->death_mutex);
}