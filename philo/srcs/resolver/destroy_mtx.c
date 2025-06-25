/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_mtx.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 21:29:08 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/25 21:31:02 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mtx_fork(t_uint nb_philo, t_node *current)
{
	while (nb_philo > 0)
	{
		pthread_mutex_destroy(&((t_fork *)current->content)->mutex);
		current = current->prev->prev;
		nb_philo--;
	}
}

void	destroy_mtx_philo(t_uint nb_philo, t_node *current)
{
	while (nb_philo > 0)
	{
		pthread_mutex_destroy(&((t_philo *)current->content)->mtx_eat);
		current = current->prev->prev;
		nb_philo--;
	}
}
