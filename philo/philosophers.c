#include "philosophers.h"

int struct_init(t_philos_table *table, t_params arg)
{
	if(!table)
		return 0;
	table->philos = malloc(arg.nb_philos * sizeof(t_philo));
	
	if(!table->philos)
		return 0;
	return 1;
}

void *philosophy(void *philosopher)
{
	t_philo *philo = (t_philo *)philosopher;
	// while (1)
	// {
	// 	//think
	// 	//
	// 	//take forks
	// 	//	//if (philo->id % 2 == 0)
	// 	//	//	pthread_mutex_lock(philo->left_fork);	
	// 	//	//else
	// 	//	//	pthread_mutex_lock(philo->right_fork);
	// 	//	//pthread_mutex_lock(philo->left_fork);


	// 	//eat
	// 	//sleep
	// }
	return NULL;

}

void philosophy_start(t_philos_table *table)
{
	pthread_t	*philos_thread;
	int			i;

	fprintf(stderr, "%lu\n", table->params.nb_philos);
	philos_thread = malloc(table->params.nb_philos * sizeof(pthread_t));
	if (!philos_thread)
		return ;
	i = -1;
	while (++i < table->params.nb_philos)
		pthread_create(&philos_thread[i], NULL, &philosophy, &table->philos[i]);
	i = -1;
	while (++i < table->params.nb_philos)
		pthread_join(philos_thread[i], NULL);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	table = malloc(sizeof(t_philos_table));
	if (!struct_init(table, args))
		return ;
	philosophy_start(table);
}
