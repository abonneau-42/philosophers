/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:48:57 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/18 17:21:32 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parser(const t_args args, t_philo_args *philo_args)
{
	return (get_args(args, (t_get_args_entry[5]){
			{&philo_args->nb_philo, UNSIGNED_INT, REQUIRED},
			{&philo_args->lifetime, UNSIGNED_INT, REQUIRED},
			{&philo_args->time_to_eat, UNSIGNED_INT, REQUIRED},
			{&philo_args->time_to_sleep, UNSIGNED_INT, REQUIRED},
			{&philo_args->ph_meal_goal, UNSIGNED_INT, OPTIONAL}
		}, 5));
}
