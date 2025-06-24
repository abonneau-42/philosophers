/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:03 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/24 15:42:45 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_args	philo_args;
	t_node			*node_list;
	t_common_data	common_data;

	common_data.is_completed_init = FALSE;
	node_list = NULL;
	if (!parser((t_args){argc, argv}, &philo_args))
		return (1);
	if (!initialiser(&philo_args, &node_list))
	{
		printf("Malloc error on initialiser\n");
		free_list(&node_list, FALSE);
		return (1);
	}
	resolver(&philo_args, &node_list, &common_data);
	free_list(&node_list, common_data.is_completed_init);
	return (0);
}
