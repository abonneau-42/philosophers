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

void	routine(void *arg)
{
	const t_node *node = (t_node *)arg;
	t_fork *l_fork = ((t_fork *)((node->prev)->content));
	t_fork *r_fork = ((t_fork *)((node->next)->content));
    t_philo *philo = (t_philo *)node->content;

    printf("Routine du philosophe %u\n", philo->id);
	philo->is_ready = TRUE;
	pthread_mutex_lock(&philo->data->all_philo_is_ready);
	pthread_mutex_unlock(&philo->data->all_philo_is_ready);
	philo->last_time_eaten = get_time();
	if (philo->id % 2)
		ph_sleep(philo->data->args->time_to_eat / 2, philo);

	// Verrouiller le mutex avant de modifier la variable partagée
	while (!ph_is_dead(philo) && !ph_get_dead(philo->data))
	{
		ph_take_forks(philo, l_fork, r_fork);
		print_action(eating, philo);
		ph_sleep(philo->data->args->time_to_eat, philo);
		ph_inc_meal_count(philo);
		fk_put(l_fork);
		fk_put(r_fork);
		print_action(sleeping, philo);
		ph_sleep(philo->data->args->time_to_sleep, philo);
		print_action(thinking, philo);
		usleep(100); // Petite pause pour éviter une boucle trop rapide
	}
	fk_put(l_fork);
	fk_put(r_fork);
}
