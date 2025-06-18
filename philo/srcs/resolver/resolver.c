/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/18 16:20:49 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_philos_and_forks(
	t_philo_args *args,
	t_node *current,
	t_common_data *common_data,
	t_uint *i
)
{
	t_philo	*ph;

	while ((*i)++ < args->nb_philo)
	{
		ph = (t_philo *)current->content;
		ph->data = common_data;
		if (pthread_mutex_init(&ph->mtx_eat, NULL))
			return (FALSE);
		if (args->ph_meal_goal > 0 && pthread_create(&ph->thread, NULL,
				(void *)ph_worker, (void *)current))
			return (FALSE);
		else if (args->ph_meal_goal == 0 && pthread_create(&ph->thread, NULL,
				(void *)ph_worker_wt_limit, (void *)current))
			return (FALSE);
		current = current->next;
		if (pthread_mutex_init(&((t_fork *)current->content)->mutex, NULL))
			return (FALSE);
		current = current->next;
	}
	return (TRUE);
}

void	destroy_mtx_and_join_valid_ph(t_uint i, t_node *current)
{
	if (current->type == FORK)
	{
		pthread_mutex_destroy(&((t_philo *)current->content)->mtx_eat);
		pthread_join(((t_philo *)current->content)->thread, NULL);
	}
	while (i > 0)
	{
		pthread_mutex_destroy(&((t_fork *)current->content)->mutex);
		current = current->prev;
		pthread_mutex_destroy(&((t_philo *)current->content)->mtx_eat);
		pthread_join(((t_philo *)current->content)->thread, NULL);
		current = current->prev;
		i--;
	}
	printf("Init philo thread or fork mutex error");
}

t_bool	join_philos(t_uint nb_philo, t_node *current)
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

int	init_common_data(t_philo_args *args, t_common_data *common_data)
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

void	resolver(t_philo_args *args, t_node **node)
{
	t_common_data	common_data;
	const t_data	data = (t_data){.common_data = &common_data, .node = *node};
	pthread_t		th_manager;

	if (!init_common_data(args, &common_data))
	{
		printf("Init mutex error");
		return ;
	}
	if (!create_manager(&th_manager, &data, args->ph_meal_goal))
	{
		printf("Init manager thread error");
		destroy_all_common_mtx(&common_data);
		return ;
	}
	return (init_and_join(args, node, &common_data, th_manager));
}
