/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/25 21:00:35 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_all_common_mtx(t_common_data *common_data)
{
	pthread_mutex_destroy(&common_data->death_mutex);
	pthread_mutex_destroy(&common_data->all_philo_is_ready);
	pthread_mutex_destroy(&common_data->nb_philos_ready_mtx);
	pthread_mutex_destroy(&common_data->eating_mutex);
}

static int	create_common_mutex(t_common_data *common_data)
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

static int	init_common_data(t_philo_args *args, t_common_data *common_data)
{
	if (!create_common_mutex(common_data))
		return (FALSE);
	if (args->time_to_eat > 2000)
		common_data->max_duration = 2000 * USLEEP_DURATION_MANAGER;
	else
		common_data->max_duration = args->time_to_eat * USLEEP_DURATION_MANAGER;
	common_data->args = args;
	common_data->start_time = get_time();
	common_data->is_simulation_over = FALSE;
	common_data->philo_is_dead = FALSE;
	common_data->philos_eating = 0;
	common_data->nb_philos_ready = 0;
	return (TRUE);
}

static t_bool	create_manager(
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

void	resolver(t_philo_args *args, t_node **node, t_common_data *cdata)
{
	const t_data	data = (t_data){.common_data = cdata, .node = *node};
	pthread_t		th_manager;

	if (!init_common_data(args, cdata))
	{
		printf("Init mutex error\n");
		return ;
	}
	if (!create_manager(&th_manager, &data, args->ph_meal_goal))
	{
		printf("Init manager thread error\n");
		destroy_all_common_mtx(cdata);
		return ;
	}
	return (init_and_join(args, node, cdata, th_manager));
}
