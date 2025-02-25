/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:42 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/25 20:21:25 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_parse_error
{
	PARAMS_VALID,
	PARAMS_NOT_VALID,
	PARAMS_NOT_PRESENT
}	t_parse_error;

typedef struct s_args
{
	int		argc;
	char	**argv;
}	t_args;

typedef enum e_bool
{
	FALSE = 0,
	TRUE = 1
}	t_bool;

typedef struct s_philo_args
{
	unsigned int	number_of_philosophers;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	number_of_times_each_philosopher_must_eat;
}	t_philo_args;

typedef int			(*t_is_type_callback)(const char *, void *);

typedef enum e_is_type
{
	INT,
	UNSIGNED_INT
}	t_is_type;

typedef enum e_optional
{
	REQUIRED,
	OPTIONAL
}	t_optional;

typedef struct s_get_args_entry
{
	void			*value;
	t_is_type		type;
	t_optional		optional;
}	t_get_args_entry;

typedef struct s_node
{
	struct s_node	*prev;
	struct s_node	*next;
	void			*content;
}	t_node;

typedef struct s_philo
{
	unsigned int	id;
	unsigned int	last_time_eaten;
	pthread_t		thread;
}	t_philo;

typedef struct s_fork
{
	unsigned int	id;
	t_bool			is_taken;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_routine_args
{
	t_node			*philo_node;
	t_philo_args	*philo_args;
}	t_routine_args;

t_parse_error	get_arg(const t_args args, int param_number, t_get_args_entry entry);
void			get_args(const t_args args, t_get_args_entry *entries, int entries_count);

int		parser(const t_args args, t_philo_args *philo_args);
int		initialiser(t_philo_args *philo_args, t_node **node_list);
int		resolver(t_philo_args *philo_args, t_node **node_list);
void	free_list(t_node **node_list);

long	ft_atol(const char *nptr);
int		is_number(const char *str);
size_t	ft_strlen(const char *s);
int		is_int(const char *chr, void *number);
int is_unsigned_int(const char *chr, void *number);

void	lstadd_bidir_front(t_node **node_list, void *content);
void	lstadd_bidir_back(t_node **node_list, void *content);
#endif