/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fk_actions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:46:34 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 23:46:56 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	fk_take(t_philo *philo, t_fork *fork)
{
	t_bool	is_available;

	pthread_mutex_lock(&fork->mutex);
	is_available = fork->is_available;
	fork->is_available = FALSE;
	pthread_mutex_unlock(&fork->mutex);
	if (is_available)
		print_action(taking, philo);
	return (is_available);
}

static void	fk_put(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_available = TRUE;
	pthread_mutex_unlock(&fork->mutex);
}

void	fk_puts(t_fork *l_fork, t_fork *r_fork)
{
	fk_put(l_fork);
	fk_put(r_fork);
}
