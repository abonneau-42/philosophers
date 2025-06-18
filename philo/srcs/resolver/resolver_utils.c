/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:03:10 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/18 16:21:36 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_common_mutex(t_common_data *common_data)
{
	if (pthread_mutex_init(&common_data->death_mutex, NULL))
		return (FALSE);
	if (pthread_mutex_init(&common_data->all_philo_is_ready, NULL))
	{
		pthread_mutex_destroy(&common_data->death_mutex);
		return (FALSE);
	}
	if (pthread_mutex_init(&common_data->nb_philos_ready_mtx, NULL))
	{
		pthread_mutex_destroy(&common_data->death_mutex);
		pthread_mutex_destroy(&common_data->all_philo_is_ready);
		return (FALSE);
	}
	if (pthread_mutex_init(&common_data->eating_mutex, NULL))
	{
		pthread_mutex_destroy(&common_data->death_mutex);
		pthread_mutex_destroy(&common_data->all_philo_is_ready);
		pthread_mutex_destroy(&common_data->nb_philos_ready_mtx);
		return (FALSE);
	}
	return (TRUE);
}

t_bool	create_manager(
	pthread_t *manager_thread,
	const t_data *data,
	t_uint ph_meal_goal
)
{
	if (ph_meal_goal > 0)
	{
		if (pthread_create(manager_thread, NULL, manager, (void *)(data)))
			return (FALSE);
	}
	else if (pthread_create(manager_thread, NULL, manager_wt_limit,
			(void *)(data)))
		return (FALSE);
	return (TRUE);
}

void	destroy_all_common_mtx(t_common_data *common_data)
{
	pthread_mutex_destroy(&common_data->death_mutex);
	pthread_mutex_destroy(&common_data->all_philo_is_ready);
	pthread_mutex_destroy(&common_data->nb_philos_ready_mtx);
	pthread_mutex_destroy(&common_data->eating_mutex);
}

void	init_and_join(
	t_philo_args *args,
	t_node **node,
	t_common_data *common_data,
	pthread_t th_manager
)
{
	t_uint	i;

	if (!init_philos_and_forks(args, *node, common_data, &i))
	{
		ph_stop_all(common_data);
		pthread_mutex_lock(&common_data->death_mutex);
		common_data->philo_is_dead = TRUE;
		pthread_mutex_unlock(&common_data->death_mutex);
		if (pthread_join(th_manager, NULL))
			return ;
		destroy_mtx_and_join_valid_ph(i, *node);
		destroy_all_common_mtx(common_data);
	}
	else
	{
		if (pthread_join(th_manager, NULL))
			return ;
		if (join_philos(args->nb_philo, *node))
			return ;
	}
}
