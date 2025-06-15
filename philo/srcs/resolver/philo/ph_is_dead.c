/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_is_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:27:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 17:01:24 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ph_is_dead(t_philo *philo)
{
	const __uint64_t	ts_current = get_time();

	if (ts_current - philo->lts_eat <= philo->data->args->lifetime)
		return (FALSE);

	printf("//\nts_current=%lu\nts_eat____=%lu\ntime=%lu\nlifetime=%u\ncalcul=%i\n", ts_current, philo->lts_eat, ts_current - philo->lts_eat, philo->data->args->lifetime, ts_current - philo->lts_eat <= philo->data->args->lifetime);
	print_action(dead, philo);
	return (TRUE);
}
