/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/08 23:45:04 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/25 21:00:27 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_bool	ph_is_over(t_common_data *data)
{
	t_bool	dead;

	pthread_mutex_lock(&data->death_mutex);
	dead = data->is_simulation_over;
	pthread_mutex_unlock(&data->death_mutex);
	return (dead);
}

static void	wait_all_philo_is_ready(t_data *data)
{
	t_uint	i;
	t_uint	nb_philos_ready;

	i = 0;
	pthread_mutex_lock(&data->common_data->all_philo_is_ready);
	while (i < data->common_data->args->nb_philo)
	{
		if (ph_is_over(data->common_data))
		{
			pthread_mutex_unlock(&data->common_data->all_philo_is_ready);
			return ;
		}
		pthread_mutex_lock(&data->common_data->nb_philos_ready_mtx);
		nb_philos_ready = data->common_data->nb_philos_ready;
		pthread_mutex_unlock(&data->common_data->nb_philos_ready_mtx);
		if (nb_philos_ready == data->common_data->args->nb_philo)
		{
			pthread_mutex_unlock(&data->common_data->all_philo_is_ready);
			return ;
		}
		usleep(USLEEP_DURATION_READY);
	}
}

static int	get_count(t_node *node, int nbs, t_philo *philo)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (i < nbs)
	{
		pthread_mutex_lock(&(philo->mtx_eat));
		if (philo->number_of_times_eaten
			>= philo->data->args->ph_meal_goal)
			count++;
		pthread_mutex_unlock(&(philo->mtx_eat));
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
	if (ph_is_over(data->common_data))
		return (NULL);
	while (!ph_get_dead(data->common_data))
	{
		if (get_count(data->node, data->common_data->args->nb_philo,
				data->node->content))
			break ;
		usleep(data->common_data->max_duration);
	}
	ph_stop_all(data->common_data);
	return (NULL);
}

void	*manager_wt_limit(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	wait_all_philo_is_ready(data);
	if (ph_is_over(data->common_data))
		return (NULL);
	while (!ph_get_dead(data->common_data))
		usleep(data->common_data->max_duration);
	ph_stop_all(data->common_data);
	return (NULL);
}
