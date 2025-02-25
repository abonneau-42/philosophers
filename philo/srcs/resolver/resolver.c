/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/25 18:08:22 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int resolver(t_philo_args *philo_args, t_node **node_list)
{
	pthread_t threads[NUM_THREADS];
	for (long i = 0; i < philo_args->number_of_philosophers; i++) {
        if (pthread_create(&threads[i], NULL, increment_counter, (void *)i) != 0) {
            printf("Erreur de création du thread %ld\n", i);
            return 1;
        }
    }

	return (1);
}