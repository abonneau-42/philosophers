/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ph_worker.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 21:08:48 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/18 16:58:16 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_to_eat(t_common_data *data, t_philo *philo)
{
	pthread_mutex_t	*mtx;

	mtx = &data->eating_mutex;
	while (1)
	{
		ph_is_dead(philo);
		pthread_mutex_lock(mtx);
		if (data->philos_eating <= data->args->nb_philo >> 1)
		{
			data->philos_eating++;
			pthread_mutex_unlock(mtx);
			break ;
		}
		pthread_mutex_unlock(mtx);
		usleep(USLEEP_DURATION);
	}
}

static void	done_eating(t_common_data *data)
{
	pthread_mutex_t	*mtx;

	mtx = &data->eating_mutex;
	pthread_mutex_lock(mtx);
	data->philos_eating--;
	pthread_mutex_unlock(mtx);
}

static t_bool	ph_is_over(t_common_data *data)
{
	t_bool	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->is_simulation_over;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

void	ph_worker(void *arg)
{
	const t_node	*node = (t_node *)arg;
	t_fork *const	l_fork = ((t_fork *)((node->prev)->content));
	t_fork *const	r_fork = ((t_fork *)((node->next)->content));
	t_philo *const	philo = (t_philo *)node->content;

	ph_prepare_worker(philo);
	while (!ph_is_dead(philo) && !ph_is_over(philo->data))
	{
		wait_to_eat(philo->data, philo);
		ph_take_forks(philo, l_fork, r_fork);
		print_action(eating, philo);
		ph_sleep(philo->data->args->time_to_eat, philo);
		ph_puts_forks(l_fork, r_fork);
		ph_is_dead(philo);
		done_eating(philo->data);
		ph_inc_meal_count(philo);
		print_action(sleeping, philo);
		ph_sleep(philo->data->args->time_to_sleep, philo);
		ph_is_dead(philo);
		print_action(thinking, philo);
	}
	ph_puts_forks(l_fork, r_fork);
}

void	ph_worker_wt_limit(void *arg)
{
	const t_node	*node = (t_node *)arg;
	t_fork *const	l_fork = ((t_fork *)((node->prev)->content));
	t_fork *const	r_fork = ((t_fork *)((node->next)->content));
	t_philo *const	philo = (t_philo *)node->content;

	ph_prepare_worker(philo);
	while (!ph_is_dead(philo) && !ph_is_over(philo->data))
	{
		wait_to_eat(philo->data, philo);
		ph_take_forks(philo, l_fork, r_fork);
		print_action(eating, philo);
		ph_sleep(philo->data->args->time_to_eat, philo);
		ph_puts_forks(l_fork, r_fork);
		ph_is_dead(philo);
		done_eating(philo->data);
		print_action(sleeping, philo);
		ph_sleep(philo->data->args->time_to_sleep, philo);
		ph_is_dead(philo);
		print_action(thinking, philo);
	}
	ph_puts_forks(l_fork, r_fork);
}
