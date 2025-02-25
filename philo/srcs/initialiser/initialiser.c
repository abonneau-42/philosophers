/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialiser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 17:38:58 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/25 19:54:28 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialiser(t_philo_args *philo_args, t_node **node_list)
{
	unsigned int i;
	t_philo *philo;
	t_fork	*fork;
	
	i = 0;
	while (i++ < philo_args->number_of_philosophers)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (0);
		*philo = (t_philo){.id = i, .last_time_eaten = 0};
		fork = malloc(sizeof(t_fork));
		if (!fork)
			return (0);
		*fork = (t_fork){.id = i, .is_taken = FALSE};
		lstadd_bidir_back(node_list, philo);
		lstadd_bidir_back(node_list, fork);
	}
	return (1);
}
