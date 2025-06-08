/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_inc_meal_count.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 22:31:48 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 23:31:28 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_inc_meal_count(t_philo *philo)
{
	pthread_mutex_lock(&(philo->mtx_eat));
	philo->number_of_times_eaten++;
	pthread_mutex_unlock(&(philo->mtx_eat));
}
