/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_bidir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:52:16 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 23:40:38 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lstadd_bidir_front(t_node **node_list, void *content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->content = content;
	if (!(*node_list))
	{
		new->next = new;
		new->prev = new;
		*node_list = new;
		return ;
	}
	new->next = *node_list;
	new->prev = (*node_list)->prev;
	if ((*node_list)->prev)
		(*node_list)->prev->next = new;
	(*node_list)->prev = new;
	*node_list = new;
}

void	lstadd_bidir_back(t_node **node_list, void *content)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->content = content;
	if (!(*node_list))
	{
		new->next = new;
		new->prev = new;
		*node_list = new;
		return ;
	}
	new->next = *node_list;
	new->prev = (*node_list)->prev;
	(*node_list)->prev->next = new;
	(*node_list)->prev = new;
}
