#include "philo.h"

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
	routine_args->print_mutex = args.print_mutex;
    if (pthread_create(watchdog_thread, NULL, watchdog, (void *)routine_args) != 0)
    {
        printf("Erreur de création du thread watchdog.\n");
        return (FALSE);
    }
	return (TRUE);
}
