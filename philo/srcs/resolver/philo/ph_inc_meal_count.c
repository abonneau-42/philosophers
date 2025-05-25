#include "philo.h"

void	ph_inc_meal_count(t_philo *philo)
{
	if (philo->data->args->number_of_times_each_philosopher_must_eat > 0)
	{
		pthread_mutex_lock(&(philo->mtx_eat));
		philo->number_of_times_eaten++;
		pthread_mutex_unlock(&(philo->mtx_eat));
	}
}