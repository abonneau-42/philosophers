/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:52:27 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/25 17:42:23 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static t_is_type_callback	*get_callback_is_type(void)
{
	static t_is_type_callback	callbacks[2] = {is_int, is_unsigned_int};

	return (callbacks);
}

t_parse_error	get_arg(const t_args args, int param_number,
		t_get_args_entry entry)
{
	t_is_type_callback	*callbacks;
	
	if (param_number < 0 || param_number >= args.argc)
	{
		if (entry.optional == OPTIONAL)
			return (PARAMS_VALID);
		return (PARAMS_NOT_PRESENT);
	}
	callbacks = get_callback_is_type();
	if (!(callbacks[entry.type])(args.argv[param_number], entry.value))
		return (PARAMS_NOT_VALID);
	return (PARAMS_VALID);
}

void	get_args(const t_args args, t_get_args_entry *entries, int entries_count)
{
	int	i;
	t_parse_error	status;

	i = 0;
	while (i < entries_count)
	{
		status = get_arg(args, i + 1, entries[i]);
		if (status == PARAMS_NOT_VALID)
		{
			printf("Argument %d is not valid\n", i + 1);
			exit(1);
		}
		if (status == PARAMS_NOT_PRESENT)
		{
			printf("Argument %d is not present\n", i + 1);
			exit(1);
		}
		i++;
	}
}
