# include "philo.h"
#include <stdint.h>

__uint64_t get_time(void)
{
	struct timeval tv;
	
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_state state, t_philo *philo)
{
	const __uint64_t time = get_time();
	const char	*message[] = {
		" died\n",
		" is eating\n",
		" is sleeping\n",
		" is thinking\n",
		" has taken a fork\n"
	};

	if (state == eating)
		philo->last_time_eaten = time;
	pthread_mutex_lock(&philo->data->death_mutex);
	if ((state == dead && philo->data->philo_is_dead == FALSE)
		|| philo->data->philo_is_dead == FALSE)
		printf("%zu %u%s", time,
			philo->id + 1, message[state]);
	if (state == dead)
		philo->data->philo_is_dead = TRUE;
	pthread_mutex_unlock(&philo->data->death_mutex);
}
