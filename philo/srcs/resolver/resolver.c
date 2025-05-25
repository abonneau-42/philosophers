/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/05/25 17:33:21 by abonneau         ###   ########.fr       */
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

int resolver(t_philo_args *args, t_node **node)
{
	t_uint			i;
	t_common_data	common_data;
	t_data			data;
	pthread_t		manager_thread;
	
	printf("SON GOKU\n");
	if (pthread_mutex_init(&common_data.death_mutex, NULL) || pthread_mutex_init(&common_data.all_philo_is_ready, NULL))
		return (FALSE);
	printf("SON GOKU\n");
	common_data.args = args;
	common_data.philo_is_dead = FALSE;
	data = (t_data){.common_data = &common_data, .node_list = *node};
	if (pthread_create(&manager_thread, NULL, manager, (void *)(&data)))
		return (FALSE);

	t_node *current = *node;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		t_philo *philo = (t_philo *)current->content;
		philo->data = &common_data;

		if (pthread_mutex_init(&philo->mtx_eat, NULL))
			return (FALSE);

		if (pthread_create(&philo->thread, NULL, (void *)routine, (void *)current))
			return (FALSE);

		current = current->next;
	
		t_fork *fork = (t_fork *)current->content;
		if (pthread_mutex_init(&fork->mutex, NULL))
			return (FALSE);

		current = current->next;
		i++;
	}
	
	pthread_join(manager_thread, NULL);

	current = *node;
	i = 0;
	while (i < args->number_of_philosophers)
	{
		t_philo *philo = (t_philo *)current->content;
		pthread_join(philo->thread, NULL);
		current = current->next->next;
		i++;
	}

	return (0);
}
