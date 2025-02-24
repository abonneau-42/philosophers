/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:42 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/24 18:26:14 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

typedef enum e_parse_error
{
	PARAMS_VALID,
	PARAMS_NOT_VALID,
	PARAMS_NOT_PRESENT
}	t_parse_error;

long	ft_atol(const char *nptr);
int		is_number(char *str);
size_t	ft_strlen(const char *s);
int		is_int(char *chr, int *number);
int		is_unsigned_int(char *chr, int *number);

#endif