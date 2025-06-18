/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstadd_bidir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 16:52:16 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/18 14:34:56 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lstadd_bidir_back(t_node **node_list, void *content, t_type_node type)
{
	t_node	*new;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->content = content;
	new->type = type;
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
