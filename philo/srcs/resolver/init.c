#include "philo.h"

t_bool init_mutex(t_node **node)

{
	*node = (*node)->next;
	if (pthread_mutex_init(&((t_fork *)(*node)->content)->mutex, NULL) != 0) {
		printf("Erreur d'initialisation du mutex\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool init_philo(t_routine_args args)

{
	t_routine_args *routine_args;

	routine_args = malloc(sizeof(t_routine_args));
	if (!routine_args)
	{
		printf("Erreur d'allocation mémoire\n");
		return (FALSE);
	}
	routine_args->philo_node = args.philo_node;
	routine_args->philo_args = args.philo_args;
	routine_args->death_mutex = args.death_mutex;
	routine_args->is_simulation_over = args.is_simulation_over;
	routine_args->all_philo_is_ready = args.all_philo_is_ready;
	if (pthread_create(&((t_philo *)routine_args->philo_node->content)->thread, NULL, routine, routine_args) != 0)
	{
		printf("Erreur de création du thread %u\n", ((t_philo *)routine_args->philo_node->content)->id);
		return (FALSE);
	}
	return (TRUE);
}

t_bool init_death_mutex(pthread_mutex_t *death_mutex)
{
	if (pthread_mutex_init(death_mutex, NULL) != 0)
	{
		printf("Erreur d'initialisation du mutex de mort\n");
		return (FALSE);
	}
	return (TRUE);
}

t_bool init_watcher_thread(pthread_t *watchdog_thread, t_routine_args args)
{
	t_routine_args *routine_args;
	
	routine_args = malloc(sizeof(t_routine_args));
	if (!routine_args)
	{
		printf("Erreur d'allocation mémoire\n");
		return (FALSE);
	}
	routine_args->philo_node = args.philo_node;
	routine_args->philo_args = args.philo_args;
	routine_args->death_mutex = args.death_mutex;
	routine_args->is_simulation_over = args.is_simulation_over;
	routine_args->all_philo_is_ready = args.all_philo_is_ready;
    if (pthread_create(watchdog_thread, NULL, watchdog, (void *)routine_args) != 0)
    {
        printf("Erreur de création du thread watchdog.\n");
        return (FALSE);
    }
	return (TRUE);
}

t_bool init_all_philo_is_ready_mutex(pthread_mutex_t *all_philo_is_ready)
{
	if (pthread_mutex_init(all_philo_is_ready, NULL) != 0)
	{
		printf("Erreur d'initialisation du mutex de tous les philosophes prêts\n");
		return (FALSE);
	}
	return (TRUE);
}