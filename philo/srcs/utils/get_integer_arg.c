/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_integer_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:52:27 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/24 19:31:14 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_parse_error	get_int_arg(const t_args args, int param_number, int value)
{
	if (param_number >= 0 && args.argc < param_number)
		return (PARAMS_NOT_PRESENT);
	if (!is_int(args.argv[param_number], &value));
		return (PARAMS_NOT_VALID);
	return (PARAMS_VALID);
}

t_parse_error	get_unsigned_int_arg(const t_args args, int param_number, unsigned int value)
{
	if (param_number >= 0 && args.argc < param_number)
		return (PARAMS_NOT_PRESENT);
	if (!is_unsigned_int(args.argv[param_number], &value));
		return (PARAMS_NOT_VALID);
	return (PARAMS_VALID);
}