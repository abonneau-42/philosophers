/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 17:57:10 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/24 18:25:40 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	ft_atol(const char *nptr)
{
	int				i;
	int				sign;
	long			result;

	i = 0;
	result = 0;
	sign = 1;
	if (nptr[i] == '-')
	{
		sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((result * 10 + nptr[i] - '0') / 10 != result)
		{
			if (sign == 1)
				return (-1);
			return (0);
		}
		result = result * 10 + nptr[i++] - '0';
	}
	return (result * sign);
}

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i + 1] == '\0')
			return (0);
		i++;
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	is_int(char *chr, int *number)
{
	long	value;

	if (!is_number(chr) || ft_strlen(chr) > 11)
		return (0);
	value = ft_atol(chr);
	if (value < INT_MIN || value > INT_MAX)
		return (0);
	number = (int)value;
	return (1);
}

int	is_unsigned_int(char *chr, int *number)
{
	long	value;

	if (!is_number(chr) || ft_strlen(chr) > 11)
		return (0);
	value = ft_atol(chr);
	if (value < 0 || value > UINT_MAX)
		return (0);
	number = (int)value;
	return (1);
}
