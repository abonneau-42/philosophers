/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:03 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/18 17:18:56 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_args	philo_args;
	t_node			*node_list;

	node_list = NULL;
	if (!parser((t_args){argc, argv}, &philo_args))
		return (1);
	if (!initialiser(&philo_args, &node_list))
	{
		printf("Malloc error on initialiser");
		free_list(&node_list);
		return (1);
	}
	resolver(&philo_args, &node_list);
	free_list(&node_list);
	return (0);
}
