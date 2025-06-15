/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:45:04 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/15 14:53:45 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	wait_all_philo_is_ready(t_data *data)
{
	t_uint	i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_lock(&data->common_data->all_philo_is_ready);
	while (i < data->common_data->args->nb_philo)
	{
		philo = (t_philo *)data->node->content;
		if (philo->is_ready == TRUE)
			i++;
		data->node = data->node->next->next;
		usleep(USLEEP_DURATION_READY);
	}
	pthread_mutex_unlock(&data->common_data->all_philo_is_ready);
	usleep(USLEEP_DURATION_MANAGER_OFFSET);
}

static int	get_count(t_node *node, int nbs)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < nbs)
	{
		pthread_mutex_lock(&(((t_philo *)(node->content))->mtx_eat));
		if (((t_philo *)(node->content))->number_of_times_eaten
			>= ((t_philo *)(node->content))->data->args->philo_meal_quota)
			count++;
		pthread_mutex_unlock(&(((t_philo *)(node->content))->mtx_eat));
		node = node->next->next;
		i++;
	}
	if (nbs == count)
		return (1);
	return (0);
}

void	*manager(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	wait_all_philo_is_ready(data);
	while (!ph_get_dead(data->common_data))
	{
		if (get_count(data->node, data->common_data->args->nb_philo))
			ph_stop_all(data->common_data);
		usleep(data->common_data->max_duration);
	}
	return (NULL);
}

void	*manager_wt_limit(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	wait_all_philo_is_ready(data);
	while (!ph_get_dead(data->common_data))
		usleep(data->common_data->max_duration);
	return (NULL);
}
