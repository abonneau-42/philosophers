/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/05/04 19:04:42 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*watchdog(void *arg)
{
	t_routine_args *args;
    struct timeval tv;
    long time_since_last_meal;
	t_uint i;
	t_philo *philo;

	args = (t_routine_args *)arg;
	i = 0;
	while (!*args->is_simulation_over)
	{
		while (i < args->philo_args->number_of_philosophers)
		{
			philo = (t_philo *)args->philo_node->content;
			gettimeofday(&tv, NULL);
			printf("last_time_eaten=%lu\n", (unsigned long) philo->last_time_eaten);
			printf("time=%lu\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000));
			time_since_last_meal = (tv.tv_sec * 1000 + tv.tv_usec / 1000) - philo->last_time_eaten;
			if (time_since_last_meal > args->philo_args->time_to_die)
			{
				pthread_mutex_lock(args->death_mutex);
				if (!*args->is_simulation_over)
				{
					*args->is_simulation_over = TRUE;
					print_action(DIED, philo);
				}
				pthread_mutex_unlock(args->death_mutex);
				return (NULL);
			}
			args->philo_node = args->philo_node->next->next;
			i++;
		}
		usleep(1000);
	}
    return (NULL);
}

int resolver(t_philo_args *args, t_node **node)
{
	unsigned int i;
	pthread_mutex_t	death_mutex;
	t_bool is_simulation_over;
	pthread_t watchdog_thread;
	pthread_mutex_t	all_philo_is_ready;

	is_simulation_over = FALSE;
	init_death_mutex(&death_mutex);
	init_all_philo_is_ready_mutex(&all_philo_is_ready);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		init_mutex(node);
		*node = (*node)->next;
		init_philo((t_routine_args){*node, args, &death_mutex, &is_simulation_over, &all_philo_is_ready});
		i++;
	}
	i = 0;
	init_watcher_thread(&watchdog_thread, (t_routine_args){*node, args, &death_mutex, &is_simulation_over, &all_philo_is_ready});
	while (i < args->number_of_philosophers)
	{
		pthread_join(((t_philo *)(*node)->content)->thread, NULL);
		*node = (*node)->next->next;
		i++;
	}
	pthread_join(watchdog_thread, NULL);
	return (0);
}
