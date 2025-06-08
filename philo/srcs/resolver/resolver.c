/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 21:03:15 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	init_philos_and_forks(
	t_uint nb_philo,
	t_node *current,
	t_common_data *common_data
)
{
	t_uint	i;
	t_philo	*philo;
	t_fork	*fork;

	i = 0;
	while (i++ < nb_philo)
	{
		philo = (t_philo *)current->content;
		philo->data = common_data;
		if (pthread_mutex_init(&philo->mtx_eat, NULL))
			return (TRUE);
		if (pthread_create(&philo->thread, NULL,
				(void *)ph_worker, (void *)current))
			return (TRUE);
		current = current->next;
		fork = (t_fork *)current->content;
		if (pthread_mutex_init(&fork->mutex, NULL))
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

	if (pthread_mutex_init(&common_data.death_mutex, NULL)
		|| pthread_mutex_init(&common_data.all_philo_is_ready, NULL))
		return (FALSE);
	common_data.args = args;
	common_data.philo_is_dead = FALSE;
	if (pthread_create(&manager_thread, NULL, manager, (void *)(&data)))
		return (FALSE);
	if (init_philos_and_forks(args->nb_philo, *node, &common_data))
		return (FALSE);
	if (pthread_join(manager_thread, NULL))
		return (FALSE);
	if (join_philos(args->nb_philo, *node))
		return (FALSE);
	return (0);
}
