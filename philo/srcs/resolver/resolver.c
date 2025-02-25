/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resolver.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abonneau <abonneau@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:04:44 by abonneau          #+#    #+#             */
/*   Updated: 2025/02/25 20:25:23 by abonneau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	struct timeval tv;
	
	t_routine_args *args = (t_routine_args *)arg;

    if (!args->philo_node || !args->philo_node->content) {
        printf("Erreur : philo_node ou son contenu est NULL\n");
        return NULL;
    }

    t_philo *philo = (t_philo *)args->philo_node->content;
    printf("Routine du philosophe %u\n", philo->id);

	// Verrouiller le mutex avant de modifier la variable partagée
	pthread_mutex_lock(&((t_fork *)((args->philo_node->prev)->content))->mutex);
	pthread_mutex_lock(&((t_fork *)((args->philo_node->next)->content))->mutex);

	// Manger
	usleep(args->philo_args->time_to_eat);

	gettimeofday(&tv, NULL);
	philo->last_time_eaten = tv.tv_sec * 1000 + tv.tv_usec / 1000;

    pthread_mutex_unlock(&((t_fork *)((args->philo_node->next)->content))->mutex);
    pthread_mutex_unlock(&((t_fork *)((args->philo_node->prev)->content))->mutex);

	free(args);
    return NULL;
}


int resolver(t_philo_args *philo_args, t_node **node_list)
{
	unsigned int i;

	i = 0;
	while (i < philo_args->number_of_philosophers)
	{
		t_routine_args *args = malloc(sizeof(t_routine_args));
		if (!args)
		{
			printf("Erreur d'allocation mémoire\n");
			return (1);
		}
		args->philo_node = *node_list;
		args->philo_args = philo_args;
		if (pthread_create(&((t_philo *)(*node_list)->content)->thread, NULL, routine, args) != 0)
		{
            printf("Erreur de création du thread %u\n", i);
            return (1);
        }
		*node_list = (*node_list)->next;
		if (pthread_mutex_init(&((t_fork *)(*node_list)->content)->mutex, NULL) != 0) {
			printf("Erreur d'initialisation du mutex\n");
			return (1);
		}
		*node_list = (*node_list)->next;
		i++;
	}
	i = 0;
	while (i < philo_args->number_of_philosophers)
	{
		pthread_join(((t_philo *)(*node_list)->content)->thread, NULL);
		*node_list = (*node_list)->next->next;
		i++;
	}
	return (0);
}