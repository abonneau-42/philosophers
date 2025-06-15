/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_worker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:08:48 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 18:23:34 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ph_worker(void *arg)
{
	const t_node	*node = (t_node *)arg;
	t_fork *const	l_fork = ((t_fork *)((node->prev)->content));
	t_fork *const	r_fork = ((t_fork *)((node->next)->content));
	t_philo *const	philo = (t_philo *)node->content;

	pthread_mutex_lock(&philo->data->nb_philos_ready_mtx);
	philo->data->nb_philos_ready++;
	pthread_mutex_unlock(&philo->data->nb_philos_ready_mtx);
	pthread_mutex_lock(&philo->data->all_philo_is_ready);
	pthread_mutex_unlock(&philo->data->all_philo_is_ready);
	philo->lts_eat = get_time();
	if (philo->data->args->nb_philo > 1 && philo->id % 2)
		ph_sleep(philo->data->args->time_to_eat >> 1, philo);
	while (!ph_is_dead(philo) && !ph_get_dead(philo->data))
	{
		ph_take_forks(philo, l_fork, r_fork);
		print_action(eating, philo);
		ph_sleep(philo->data->args->time_to_eat, philo);
		ph_inc_meal_count(philo);
		ph_puts_forks(l_fork, r_fork);
		print_action(sleeping, philo);
		ph_sleep(philo->data->args->time_to_sleep, philo);
		print_action(thinking, philo);
		usleep(100);
	}
	ph_puts_forks(l_fork, r_fork);
}

void	ph_worker_wt_limit(void *arg)
{
	const t_node	*node = (t_node *)arg;
	t_fork *const	l_fork = ((t_fork *)((node->prev)->content));
	t_fork *const	r_fork = ((t_fork *)((node->next)->content));
	t_philo *const	philo = (t_philo *)node->content;

	pthread_mutex_lock(&philo->data->nb_philos_ready_mtx);
	philo->data->nb_philos_ready++;
	pthread_mutex_unlock(&philo->data->nb_philos_ready_mtx);
	pthread_mutex_lock(&philo->data->all_philo_is_ready);
	pthread_mutex_unlock(&philo->data->all_philo_is_ready);
	philo->lts_eat = get_time();
	if (philo->data->args->nb_philo > 1 && philo->id % 2)
		ph_sleep(philo->data->args->time_to_eat >> 1, philo);
	while (!ph_is_dead(philo) && !ph_get_dead(philo->data))
	{
		ph_take_forks(philo, l_fork, r_fork);
		print_action(eating, philo);
		ph_sleep(philo->data->args->time_to_eat, philo);
		ph_puts_forks(l_fork, r_fork);
		print_action(sleeping, philo);
		ph_sleep(philo->data->args->time_to_sleep, philo);
		print_action(thinking, philo);
		usleep(100);
	}
	ph_puts_forks(l_fork, r_fork);
}
