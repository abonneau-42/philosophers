/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/18 15:03:10 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/25 21:02:34 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool	init_fork_mutexes(
	t_node *current,
	t_uint nb_philo
)
{
	t_uint	i;

	i = 0;
	current = current->next;
	while (i < nb_philo)
	{
		if (pthread_mutex_init(&((t_fork *)current->content)->mutex, NULL))
			break ;
		current = current->next->next;
		i++;
	}
	if (i < nb_philo)
	{
		current = current->prev->prev;
		while (i > 0)
		{
			pthread_mutex_destroy(&((t_fork *)current->content)->mutex);
			current = current->prev->prev;
			i--;
		}
		return (FALSE);
	}
	return (TRUE);
}

t_bool	init_philo_mutexes(
	t_node *current,
	t_common_data *common_data,
	t_uint nb_philo
)
{
	t_uint	i;
	t_philo	*ph;

	i = 0;
	while (i < nb_philo)
	{
		ph = (t_philo *)current->content;
		ph->data = common_data;
		if (pthread_mutex_init(&ph->mtx_eat, NULL))
			break ;
		current = current->next->next;
		i++;
	}
	if (i < nb_philo)
	{
		current = current->prev->prev;
		while (i > 0)
		{
			pthread_mutex_destroy(&((t_philo *)current->content)->mtx_eat);
			current = current->prev->prev;
			i--;
		}
		return (FALSE);
	}
	return (TRUE);
}

void	join_philos_threads(
	t_node *current,
	t_uint	size
)
{
	t_uint	i;

	i = 0;
	while (i < size)
	{
		pthread_join(((t_philo *)current->content)->thread, NULL);
		current = current->next->next;
		i++;
	}
}

t_bool	start_philos_threads(
	t_node *current,
	t_philo_args *args,
	t_uint	*size
)
{
	t_philo	*ph;

	while (*size < args->nb_philo)
	{
		ph = (t_philo *)current->content;
		if (args->ph_meal_goal > 0)
		{
			if (pthread_create(&ph->thread, NULL,
					(void *)ph_worker, (void *)current))
				return (FALSE);
		}
		else
		{
			if (pthread_create(&ph->thread, NULL,
					(void *)ph_worker_wt_limit, (void *)current))
				return (FALSE);
		}
		current = current->next->next;
		(*size)++;
	}
	return (TRUE);
}

inline void	init_and_join(
	t_philo_args *args,
	t_node **node,
	t_common_data *common_data,
	pthread_t th_manager
)
{
	t_uint	count;

	count = 0;
	if (!init_fork_mutexes(*node, args->nb_philo)
		|| !init_philo_mutexes(*node, common_data, args->nb_philo)
		|| !start_philos_threads(*node, args, &count))
	{
		ph_stop_all(common_data);
		common_data->philo_is_dead = TRUE;
		if (pthread_join(th_manager, NULL))
			return ;
		join_philos_threads(*node, count);
	}
	else
	{
		common_data->is_completed_init = TRUE;
		if (pthread_join(th_manager, NULL))
			return ;
		join_philos_threads(*node, count);
	}
	destroy_all_common_mtx(common_data);
}
