/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_worker_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:11:49 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/24 17:00:29 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_prepare_worker(t_philo *const philo)
{
	pthread_mutex_lock(&philo->data->nb_philos_ready_mtx);
	philo->data->nb_philos_ready++;
	pthread_mutex_unlock(&philo->data->nb_philos_ready_mtx);
	printf("ok\n");
	pthread_mutex_lock(&philo->data->all_philo_is_ready);
	pthread_mutex_unlock(&philo->data->all_philo_is_ready);
	printf("ok2\n");
	philo->lts_eat = get_time();
	pthread_mutex_lock(&philo->data->death_mutex);
	if (philo->data->args->nb_philo > 1 && philo->id % 2)
		ph_sleep(philo->data->args->time_to_eat >> 1, philo);
	pthread_mutex_unlock(&philo->data->death_mutex);
}
