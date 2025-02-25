/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:48:57 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/25 17:44:02 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parser(const t_args args, t_philo_args *philo_args)
{
	get_args(args, (t_get_args_entry[5]){
		{&philo_args->number_of_philosophers, UNSIGNED_INT, REQUIRED},
		{&philo_args->time_to_die, UNSIGNED_INT, REQUIRED},
		{&philo_args->time_to_eat, UNSIGNED_INT, REQUIRED},
		{&philo_args->time_to_sleep, UNSIGNED_INT, REQUIRED},
		{&philo_args->number_of_times_each_philosopher_must_eat, UNSIGNED_INT, OPTIONAL}
	}, 5);
	return (1);
}