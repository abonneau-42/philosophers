/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:03:10 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/19 18:54:36 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_mtx_and_join_valid_ph(t_uint i, t_node *current)
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
	printf("Init philo thread or fork mutex error\n");
}

static t_bool	init_philos_and_forks(
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

void	init_and_join(
	t_philo_args *args,
	t_node **node,
	t_common_data *common_data,
	pthread_t th_manager
)
{
	t_uint	i;

	i = 0;
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
