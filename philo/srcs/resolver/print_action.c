/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_action.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:03:49 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 15:16:46 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>

inline __uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	print_action(t_state state, t_philo *philo)
{
	const __uint64_t	time = get_time();
	const char			*message[] = {
		" died\n",
		" is eating\n",
		" is sleeping\n",
		" is thinking\n",
		" has taken a fork\n"
	};

	if (state == eating)
		philo->lts_eat = time;
	pthread_mutex_lock(&philo->data->death_mutex);
	if ((state == dead && philo->data->philo_is_dead == FALSE)
		|| philo->data->philo_is_dead == FALSE)
		printf("%zu %u%s", time,
			philo->id, message[state]);
	if (state == dead)
		philo->data->philo_is_dead = TRUE;
	pthread_mutex_unlock(&philo->data->death_mutex);
}
