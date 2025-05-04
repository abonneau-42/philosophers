#include "philo.h"

t_bool is_simulation_over(t_routine_args *args)
{
    t_bool result;

    pthread_mutex_lock(args->death_mutex);
    result = *args->is_simulation_over;
    pthread_mutex_unlock(args->death_mutex);
    return result;
}

t_bool is_simulation_over_in_mutex(t_routine_args *args)
{
    t_bool result;

    pthread_mutex_lock(args->death_mutex);
    result = *args->is_simulation_over;
    pthread_mutex_unlock(args->death_mutex);
	pthread_mutex_unlock(&((t_fork *)((args->philo_node->next)->content))->mutex);
	pthread_mutex_unlock(&((t_fork *)((args->philo_node->prev)->content))->mutex);
    return result;
}

void *routine(void *arg)
{
	struct timeval tv;
	
	t_routine_args *args = (t_routine_args *)arg;

    if (!args->philo_node || !args->philo_node->content) {
        printf("Erreur : philo_node ou son contenu est NULL\n");
        return NULL;
    }

    t_philo *philo = (t_philo *)args->philo_node->content;
	gettimeofday(&tv, NULL);
	philo->last_time_eaten = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    printf("Routine du philosophe %u\n", philo->id);

	philo
	pthread_mutex_lock(args->all_philo_is_ready);

	// Verrouiller le mutex avant de modifier la variable partagée
	while (!is_simulation_over(args))
	{
		print_action(THINKING, philo);

		pthread_mutex_lock(&((t_fork *)((args->philo_node->prev)->content))->mutex);
		print_action(TAKEN_FORK, philo);
		pthread_mutex_lock(&((t_fork *)((args->philo_node->next)->content))->mutex);
		print_action(TAKEN_FORK, philo);

		if (is_simulation_over_in_mutex(args))
        	break ;

		print_action(EATING, philo);
		//printf("%i\n", args->philo_args->time_to_eat);
		
		usleep(5000);
		gettimeofday(&tv, NULL);
		philo->last_time_eaten = tv.tv_sec * 1000 + tv.tv_usec / 1000;

		pthread_mutex_unlock(&((t_fork *)((args->philo_node->next)->content))->mutex);
		pthread_mutex_unlock(&((t_fork *)((args->philo_node->prev)->content))->mutex);

		if (is_simulation_over(args))
        	break ;

		print_action(SLEEPING, philo);
        usleep(args->philo_args->time_to_sleep);
	}
	

	free(args);
    return NULL;
}
