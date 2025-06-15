/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_fk_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:34:30 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 22:16:20 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	fk_take(t_philo *philo, t_fork *fork)
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

void	ph_take_forks(t_philo *philo, t_fork *r_fork, t_fork *l_fork)
{
	t_bool	has_fk_l;
	t_bool	has_fk_r;

	has_fk_l = FALSE;
	has_fk_r = FALSE;
	while (!(has_fk_l && has_fk_r))
	{
		if (ph_is_dead(philo))
			return ;
		if (!has_fk_l)
			has_fk_l = fk_take(philo, l_fork);
		if (!has_fk_r)
			has_fk_r = fk_take(philo, r_fork);
		usleep(USLEEP_DURATION);
	}
}

static void	fk_put(t_fork *fork)
{
	pthread_mutex_lock(&fork->mutex);
	fork->is_available = TRUE;
	pthread_mutex_unlock(&fork->mutex);
}

void	ph_puts_forks(t_fork *l_fork, t_fork *r_fork)
{
	fk_put(l_fork);
	fk_put(r_fork);
}
