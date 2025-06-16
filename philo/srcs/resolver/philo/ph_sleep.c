/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:46:32 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/16 19:32:01 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static __uint64_t	compute_deadline(__uint64_t duration, t_philo *philo)
{
	const __uint64_t	ts_end = get_time() + duration;
	const __uint64_t	ts_dead = philo->lts_eat + philo->data->args->lifetime;

	if (ts_dead < ts_end)
	{
		printf("D EAT:%lu; TIME:%lu; OFFSET:%li; ID:%i\n", philo->lts_eat, ts_end, ts_end - philo->lts_eat, philo->id);
		return (ts_dead);
	}
	printf("A EAT:%lu; TIME:%lu; OFFSET:%li; ID:%i\n", philo->lts_eat, ts_end, ts_end - philo->lts_eat, philo->id);
	return (ts_end);
}

void	ph_sleep(__uint64_t duration, t_philo *philo)
{
	__uint64_t	delay;

	delay = compute_deadline(duration, philo);
	while (get_time() < delay)
		usleep(USLEEP_DURATION_ACTION);
	printf("A DEL:%lu; TIME:%lu; ID:%i\n", delay - duration, get_time(), philo->id);
	ph_is_dead(philo);
}
