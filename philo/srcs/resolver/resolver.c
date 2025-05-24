/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/05/24 21:03:00 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool is_include_array_n(int i, int *array, int n)
{
	int j;

	j = 0;
	while (j < n)
	{
		if (array[j] == i)
			return (TRUE);
		j++;
	}
	return (FALSE);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = c;
	return (s);
}

void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, 0, n));
}

//void	*ft_calloc(size_t nmemb, size_t size)
//{
//	void	*ptr;
//	size_t	total_size;

//	total_size = size * nmemb;
//	if (!nmemb)
//		return (malloc(0));
//	if ((total_size / nmemb) != size)
//		return (NULL);
//	ptr = malloc(total_size);
//	if (!ptr)
//		return (NULL);
//	ft_bzero(ptr, total_size);
//	return (ptr);
//}

void	wait_all_philo_is_ready(t_routine_args *args)
{
	t_uint	i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_lock(args->all_philo_is_ready);
	while (i < args->philo_args->number_of_philosophers)
	{
		philo = (t_philo *)args->philo_node->content;
		if (philo->is_ready == TRUE)
			i++;
		args->philo_node = args->philo_node->next->next;
		usleep(100);
	}
	pthread_mutex_unlock(args->all_philo_is_ready);
	usleep(20);
}

int resolver(t_philo_args *args, t_node **node)
{
	t_uint			i;
	t_common_data	common_data;
	t_data			data;
	pthread_t		manager_thread;
	
	if (!pthread_mutex_init(&common_data.death_mutex, NULL) && !pthread_mutex_init(&common_data.all_philo_is_ready, NULL))
		return (FALSE);
	common_data.args = args;
	data = (t_data){.common_data = &common_data, .node_list = *node};
	if (!pthread_create(&manager_thread, NULL, manager, (void *)(&data)))
		return (FALSE);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		if (!pthread_mutex_init(&((t_fork *)(*node)->content)->mutex, NULL));
			return (FALSE);
		*node = (*node)->next;
		((t_philo *)(*node)->content)->data = &common_data;
		if (!pthread_create(&((t_philo *)(*node)->content)->thread, NULL, routine, (void *)(*node)))
			return (FALSE);
		i++;
	}
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(((t_philo *)(*node)->content)->thread, NULL);
		*node = (*node)->next->next;
		i++;
	}
	return (0);
}
