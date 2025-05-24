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

	pthread_mutex_t *l_fork = &((t_fork *)((args->philo_node->prev)->content))->mutex;
	pthread_mutex_t *r_fork = &((t_fork *)((args->philo_node->next)->content))->mutex;

    printf("Routine du philosophe %u\n", philo->id);
	philo->is_ready = TRUE;
	pthread_mutex_unlock(args->all_philo_is_ready);
	usleep(10 * philo->id);
	gettimeofday(&tv, NULL);
	philo->last_time_eaten = (tv.tv_sec * 1000 + tv.tv_usec / 1000);
	pthread_mutex_lock(args->all_philo_is_ready);

	// Verrouiller le mutex avant de modifier la variable partagée
	while (!is_simulation_over(args))
	{
		ph_take_forks(philo, l_fork, r_fork, args->print_mutex);
		print_action(eating, philo);

		fk_put(l_fork);
		fk_put(r_fork);



















		//print_action(THINKING, philo, args->print_mutex);


		//if (is_simulation_over_in_mutex(args))
        //	break ;
		////printf("Philosophe %u mange\n", philo->id);
		//usleep(args->philo_args->time_to_eat);
		//gettimeofday(&tv, NULL);
		//philo->last_time_eaten = tv.tv_sec * 1000 + tv.tv_usec / 1000;
		//philo->number_of_times_eaten++;
		//print_action(EATING, philo, args->print_mutex);

		//if (philo->id % 2 == 0) {
		//	pthread_mutex_unlock(right_fork);
		//	pthread_mutex_unlock(left_fork);
		//	print_action(PUT_FORK_BACK, philo, args->print_mutex);
		//} else {
		//	pthread_mutex_unlock(left_fork);
		//	pthread_mutex_unlock(right_fork);
		//	print_action(PUT_FORK_BACK, philo, args->print_mutex);
		//}

		//if (is_simulation_over(args))
        //	break ;

        //usleep(args->philo_args->time_to_sleep);
		//print_action(SLEEPING, philo, args->print_mutex);
	}
	
	free(args);
    return NULL;
}
