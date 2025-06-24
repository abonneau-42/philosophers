/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 19:55:43 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/24 14:36:59 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	list_size(t_node *node_list)
{
	int		size;
	t_node	*start;

	size = 0;
	start = node_list;
	if (node_list)
	{
		size++;
		node_list = node_list->next;
		while (node_list != start)
		{
			size++;
			node_list = node_list->next;
		}
	}
	return (size);
}

void	free_list(t_node **node_list, t_bool is_free_mutex)
{
	int		size;
	int		i;
	t_node	*tmp;

	size = list_size(*node_list);
	i = 0;
	while (i < size)
	{
		tmp = *node_list;
		*node_list = (*node_list)->next;
		free(tmp->content);
		if (is_free_mutex)
		{
			if (tmp->type == FORK)
				pthread_mutex_destroy(&((t_fork *)tmp->content)->mutex);
			else
				pthread_mutex_destroy(&((t_philo *)tmp->content)->mtx_eat);
		}
		free(tmp);
		i++;
	}
}
