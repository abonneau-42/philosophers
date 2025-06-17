/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_is_dead.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:27:17 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/17 03:34:53 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	ph_is_dead(t_philo *philo)
{
	const __uint64_t	ts_current = get_time();

	if (ts_current - philo->lts_eat <= philo->data->args->lifetime)
		return (FALSE);
	print_action(dead, philo);
	return (TRUE);
}
