/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:46:32 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 22:24:51 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

__uint64_t	compute_deadline(__uint64_t duration, t_philo *philo)
{
	const __uint64_t	ts_current = get_time();
	const __uint64_t	ts_end = ts_current + duration;
	const __uint64_t	ts_dead = philo->lts_eat + philo->data->args->lifetime;

	if (ts_dead < ts_end)
		return (ts_dead + 1);
	return (ts_end);
}

void	ph_sleep(__uint64_t duration, t_philo *philo)
{
	__uint64_t	ts_deadline;

	ts_deadline = compute_deadline(duration, philo);
	while (get_time() < ts_deadline)
		usleep(USLEEP_DURATION_ACTION);
	ph_is_dead(philo);
}
