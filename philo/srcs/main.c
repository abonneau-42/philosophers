/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:03 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 20:58:33 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_philo_args	philo_args;
	t_node	*node_list = NULL;
	
	parser((t_args){argc, argv}, &philo_args);
	printf("-------------------------------------\n");
	printf("number_of_times_each_philosopher_must_eat: %u\n", philo_args.number_of_times_each_philosopher_must_eat);
	printf("-------------------------------------\n");

	initialiser(&philo_args, &node_list);
	resolver(&philo_args, &node_list);
	free_list(&node_list);
}