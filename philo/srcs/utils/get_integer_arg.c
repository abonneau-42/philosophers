/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_integer_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:52:27 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/24 18:28:45 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_parse_error	get_int_arg(int argc, char **argv, int param_number, int value)
{
	if (param_number >= 0 && argc < param_number)
		return (PARAMS_NOT_PRESENT);
	if (!is_int(argv[param_number], &value));
		return (PARAMS_NOT_VALID);
	return (PARAMS_VALID);
}

t_parse_error	get_unsigned_int_arg(int argc, char **argv, int param_number, unsigned int value)
{
	if (param_number >= 0 && argc < param_number)
		return (PARAMS_NOT_PRESENT);
	if (!is_unsigned_int(argv[param_number], &value));
		return (PARAMS_NOT_VALID);
	return (PARAMS_VALID);
}