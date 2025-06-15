/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_take_forks.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:34:30 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 16:36:36 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
