/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/05/04 22:52:39 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_bool is_include_array_n(int i, int *array, int n)
{
	int j;

	j = 0;
	while (j < n)
	{
		if (array[j] == i)
			return (TRUE);
		j++;
	}
	return (FALSE);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = c;
	return (s);
}

void	*ft_bzero(void *s, size_t n)
{
	return (ft_memset(s, 0, n));
}

//void	*ft_calloc(size_t nmemb, size_t size)
//{
//	void	*ptr;
//	size_t	total_size;

//	total_size = size * nmemb;
//	if (!nmemb)
//		return (malloc(0));
//	if ((total_size / nmemb) != size)
//		return (NULL);
//	ptr = malloc(total_size);
//	if (!ptr)
//		return (NULL);
//	ft_bzero(ptr, total_size);
//	return (ptr);
//}

void	wait_all_philo_is_ready(t_routine_args *args)
{
	t_uint	i;
	t_philo	*philo;

	i = 0;
	pthread_mutex_lock(args->all_philo_is_ready);
	while (i < args->philo_args->number_of_philosophers)
	{
		philo = (t_philo *)args->philo_node->content;
		if (philo->is_ready == TRUE)
			i++;
		args->philo_node = args->philo_node->next->next;
		usleep(100);
	}
	pthread_mutex_unlock(args->all_philo_is_ready);
	usleep(20);
}

t_bool	has_dead_handler(t_routine_args *args, t_philo *philo, int *already_counted)
{
	long	time_since_last_meal;
	struct	timeval tv;
	
	gettimeofday(&tv, NULL);
	//printf("gettimeofday: %ld\n", (tv.tv_sec * 1000 + tv.tv_usec / 1000));
	//printf("philo->last_time_eaten: %ld\n", philo->last_time_eaten);
	
	time_since_last_meal = (tv.tv_sec * 1000000 + tv.tv_usec) - philo->last_time_eaten;
	if (time_since_last_meal > args->philo_args->time_to_die)
	{
		pthread_mutex_lock(args->death_mutex);
		if (!*args->is_simulation_over)
		{
			*args->is_simulation_over = TRUE;
			print_action(DIED, philo);
		}
		pthread_mutex_unlock(args->death_mutex);
		free(already_counted);
		free(args);
		return (TRUE);
	}
	return (FALSE);
}

t_bool	has_must_eat_reach_handler(t_routine_args *args, t_philo *philo, int *already_counted)
{
	static t_uint j = 0;

	if (args->philo_args->number_of_times_each_philosopher_must_eat && philo->number_of_times_eaten == args->philo_args->number_of_times_each_philosopher_must_eat && !is_include_array_n(philo->id, already_counted, args->philo_args->number_of_philosophers))
	{
		already_counted[j] = philo->id;
		j++;
	}
	if (j == args->philo_args->number_of_philosophers)
	{
		*args->is_simulation_over = TRUE;
		free(already_counted);
		free(args);
		return (TRUE);
	}
	return (FALSE);
}



void	*watchdog(void *arg)
{
	t_routine_args *args;
	t_uint i;
	t_philo *philo;
	int		*already_counted;
	
	args = (t_routine_args *)arg;
	i = 0;
	already_counted = malloc(sizeof(int) * args->philo_args->number_of_philosophers);
	ft_bzero(already_counted, sizeof(int) * args->philo_args->number_of_philosophers);
	
	wait_all_philo_is_ready(args);
	while (!*args->is_simulation_over)
	{
		while (i < args->philo_args->number_of_philosophers)
		{
			philo = (t_philo *)args->philo_node->content;
			if (has_dead_handler(args, philo, already_counted))
				return (NULL);
			if (has_must_eat_reach_handler(args, philo, already_counted))
				return (NULL);
			args->philo_node = args->philo_node->next->next;
			i++;
		}
		usleep(10);
		i = 0;
	}
	free(already_counted);
	free(args);
    return (NULL);
}

int resolver(t_philo_args *args, t_node **node)
{
	unsigned int i;
	pthread_mutex_t	death_mutex;
	t_bool is_simulation_over;
	pthread_t watchdog_thread;
	pthread_mutex_t	all_philo_is_ready;

	is_simulation_over = FALSE;
	init_death_mutex(&death_mutex);
	init_all_philo_is_ready_mutex(&all_philo_is_ready);
	init_watcher_thread(&watchdog_thread, (t_routine_args){*node, args, &death_mutex, &is_simulation_over, &all_philo_is_ready});
	usleep(1000);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		init_mutex(node);
		*node = (*node)->next;
		init_philo((t_routine_args){*node, args, &death_mutex, &is_simulation_over, &all_philo_is_ready});
		i++;
	}
	pthread_join(watchdog_thread, NULL);
	i = 0;
	while (i < args->number_of_philosophers)
	{
		pthread_join(((t_philo *)(*node)->content)->thread, NULL);
		*node = (*node)->next->next;
		i++;
	}
	return (0);
}
