/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/17 02:21:35 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_philos_and_forks(
	t_philo_args *args,
	t_node *current,
	t_common_data *common_data
)
{
	t_uint	i;
	t_philo	*ph;

	i = 0;
	while (i++ < args->nb_philo)
	{
		ph = (t_philo *)current->content;
		ph->data = common_data;
		if (pthread_mutex_init(&ph->mtx_eat, NULL))
			return (TRUE);
		if (args->philo_meal_quota > 0)
		{
			if (pthread_create(&ph->thread, NULL,
					(void *)ph_worker, (void *)current))
				return (TRUE);
		}
		else if (pthread_create(&ph->thread, NULL,
				(void *)ph_worker_wt_limit, (void *)current))
			return (TRUE);
		current = current->next;
		if (pthread_mutex_init(&((t_fork *)current->content)->mutex, NULL))
			return (TRUE);
		current = current->next;
	}
	return (FALSE);
}

static t_bool	join_philos(t_uint nb_philo, t_node *current)
{
	t_uint	i;
	t_philo	*philo;

	i = 0;
	while (i++ < nb_philo)
	{
		philo = (t_philo *)current->content;
		if (pthread_join(philo->thread, NULL))
			return (TRUE);
		current = current->next->next;
	}
	return (FALSE);
}

int	resolver(t_philo_args *args, t_node **node)
{
	t_common_data	common_data;
	const t_data	data = (t_data){.common_data = &common_data, .node = *node};
	pthread_t		manager_thread;

	if (args->time_to_eat > 2000)
		common_data.max_duration = 2000 * USLEEP_DURATION_MANAGER;
	else
		common_data.max_duration = args->time_to_eat * USLEEP_DURATION_MANAGER;
	if (pthread_mutex_init(&common_data.death_mutex, NULL)
		|| pthread_mutex_init(&common_data.all_philo_is_ready, NULL)
		|| pthread_mutex_init(&common_data.nb_philos_ready_mtx, NULL)
		|| pthread_mutex_init(&common_data.eating_mutex, NULL))
		return (FALSE);
	common_data.args = args;
	common_data.start_time = get_time();
	common_data.is_simulation_over = FALSE;
	common_data.philo_is_dead = FALSE;
	common_data.philos_eating = 0;
	common_data.nb_philos_ready = 0;
	if (args->philo_meal_quota > 0)
	{
		if (pthread_create(&manager_thread, NULL, manager, (void *)(&data)))
			return (FALSE);
	}
	else if (pthread_create(&manager_thread, NULL, manager_wt_limit,
			(void *)(&data)))
		return (FALSE);
	if (init_philos_and_forks(args, *node, &common_data))
		return (FALSE);
	if (pthread_join(manager_thread, NULL))
		return (FALSE);
	if (join_philos(args->nb_philo, *node))
		return (FALSE);
	return (0);
}
