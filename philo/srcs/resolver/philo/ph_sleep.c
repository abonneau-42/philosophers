/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:46:32 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 17:50:56 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_delay	compute_deadline(__uint64_t duration, t_philo *philo)
{
	const __uint64_t	ts_current = get_time();
	const __uint64_t	ts_end = ts_current + duration;
	const __uint64_t	ts_dead = philo->lts_eat + philo->data->args->lifetime;

	if (ts_dead < ts_end)
		return ((t_delay){ts_dead - (philo->data->args->lifetime >> 2), ts_dead});
	return ((t_delay){ts_end - (duration >> 2), ts_end});
}

void	ph_sleep(__uint64_t duration, t_philo *philo)
{
	t_delay	delay;

	delay = compute_deadline(duration, philo);
	if (get_time() - delay.ts_75 > 30)
		while (get_time() < delay.ts_75)
			usleep(25000);
	while (get_time() < delay.end)
		usleep(USLEEP_DURATION_ACTION);
	ph_is_dead(philo);
}
