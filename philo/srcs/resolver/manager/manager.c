#include "philo.h"

void	wait_all_philo_is_ready(t_data *data)
{
	t_uint	i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_lock(&data->common_data->all_philo_is_ready);
	while (i < data->common_data->args->number_of_philosophers)
	{
		philo = (t_philo *)data->node_list->content;
		if (philo->is_ready == TRUE)
			i++;
		args->philo_node = ((t_philo *)data->node_list->content)->next->next;
		usleep(100);
	}
	pthread_mutex_unlock(&data->common_data->all_philo_is_ready);
	usleep(20);
}

void	*manager(void *arg)
{
	t_data *data;
	
	data = (t_data *)arg;
	wait_all_philo_is_ready(data);

	while (!ph_get_dead(data))
	{
		usleep(data->time_to_eat * 500);
	}


    return (NULL);
}
