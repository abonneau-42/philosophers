/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:38:58 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/19 18:56:07 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialiser(t_philo_args *philo_args, t_node **node_list)
{
	unsigned int	i;
	t_philo			*philo;
	t_fork			*fork;

	i = 0;
	while (i++ < philo_args->nb_philo)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (FALSE);
		*philo = (t_philo){.id = i, .lts_eat = 0, .is_ready = FALSE,
			.number_of_times_eaten = 0};
		if (!lstadd_bidir_back(node_list, philo, PHILO))
			return (FALSE);
		fork = malloc(sizeof(t_fork));
		if (!fork)
			return (FALSE);
		*fork = (t_fork){.id = i, .is_available = TRUE};
		if (!lstadd_bidir_back(node_list, fork, FORK))
			return (FALSE);
	}
	return (TRUE);
}
