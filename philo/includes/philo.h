/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 16:45:42 by abonneau          #+#    #+#             */
/*   Updated: 2025/06/08 22:20:14 by abonneau         ###   ########.fr       */
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

typedef unsigned int t_uint;

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
	unsigned int	nb_philo;
	unsigned int	lifetime;
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

typedef struct s_common_data
{
	t_philo_args	*args;
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	all_philo_is_ready;
	t_bool			philo_is_dead;
}	t_common_data;

typedef struct s_philo
{
	t_uint			id;
	size_t			lts_eat;
	t_bool 			is_ready;
	t_uint			number_of_times_eaten;
	pthread_mutex_t	mtx_eat;
	pthread_t		thread;
	t_common_data	*data;
}	t_philo;

typedef struct s_fork
{
	t_uint			id;
	t_bool			is_available;
	pthread_mutex_t	mutex;
}	t_fork;

typedef struct s_routine_args
{
	t_node			*philo_node;
	t_philo_args	*philo_args;
	pthread_mutex_t	*death_mutex;
	t_bool			*is_simulation_over;
	pthread_mutex_t	*all_philo_is_ready;
	pthread_mutex_t *print_mutex;
}	t_routine_args;

typedef struct s_data
{
	t_common_data	*common_data;
	t_node			*node;
}	t_data;


# define  TAKEN_FORK " has taken a fork\n"
# define  EATING " is eating\n"
# define  SLEEPING " is sleeping\n"
# define  THINKING " is thinking\n"
# define  PUT_FORK_BACK " put fork back\n"
# define  DIED " died\n"

typedef enum e_state
{
	dead,
	eating,
	sleeping,
	thinking,
	taking
}	t_state;

# define USLEEP_DURATION 200
# define USLEEP_DURATION_ACTION 250


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

void	*watchdog(void *arg);
void	ph_worker(void *arg);
//t_bool	init_philo(t_routine_args args);
//t_bool	init_mutex(t_node **node);
//t_bool	init_death_mutex(pthread_mutex_t *death_mutex);
t_bool	init_watcher_thread(pthread_t *watchdog_thread, t_routine_args args);
//t_bool	init_all_philo_is_ready_mutex(pthread_mutex_t *all_philo_is_ready);

//t_bool init_print_mutex(pthread_mutex_t *print_mutex);

void	print_action(t_state state, t_philo *philo);
t_bool	fk_take(t_philo *philo, t_fork *fork);
//void	fk_put(t_fork *fork);

void	ph_take_forks(t_philo *philo, t_fork *r_fork, t_fork *l_fork);


__uint64_t get_time(void);


void	*manager(void *arg);

void	ph_sleep(__uint64_t duration, t_philo *philo);

void	ph_inc_meal_count(t_philo *philo);

t_bool	ph_get_dead(t_common_data *data);
t_bool	ph_is_dead(t_philo *philo);

void	ph_stop_all(t_common_data *data);

void	fk_puts(t_fork *l_fork, t_fork *r_fork);







#endif