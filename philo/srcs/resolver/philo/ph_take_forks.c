#include "philo.h"

t_bool	ph_take_forks(t_philo *philo, t_fork *r_fork, t_fork *l_fork, pthread_mutex_t *print_mutex)
{
	int		put_left;
	int		put_right;

	put_left = 0;
	put_right = 0;
	while (put_left + put_right < 2)
	{
		if (ph_is_dead(philo))
			break ;
		if (!put_left)
			put_left = fk_take(philo, l_fork, print_mutex);
		if (!put_right)
			put_right = fk_take(philo, r_fork, print_mutex);
		usleep(200);
	}
	return (TRUE);
}
