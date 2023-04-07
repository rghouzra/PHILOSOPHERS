#include "philosophers.h"

int struct_init(t_philos_table *table, t_params arg)
{
	if(!table)
		return 0;
	pthread_mutex_init(table->left_fork, NULL);
	pthread_mutex_init(table->right_fork, NULL);
	if(!table->philos)
		return 0;
	return 1;
}

void philo_take_fork(t_philos_table *philo)
{
	printf("philo id %d take fork\n", philo->philos->id);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

void philo_eat(t_philos_table *philo)
{
	printf("philo id %d eat\n", philo->philos->id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void philo_sleep(t_philos_table *philo)
{
	printf("philo id %d sleep\n", philo->philos->id);
	usleep(philo->params.time_to_sleep);
}

void *philosophy(void *philosopher)
{
	t_philos_table *philo = (t_philos_table *)philosopher;

	while (1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return NULL;
}

void philosophy_start(t_philos_table *table)
{
	pthread_t	*philos_thread;
	int			i;

	philos_thread = malloc(table->params.nb_philos * sizeof(pthread_t));
	table->philos = malloc(sizeof(t_philo));
	if (!philos_thread)
		return ;
	i = -1;
	while (++i < table->params.nb_philos)
	{
		table->philos->id = i;
		pthread_create(&philos_thread[i], NULL, &philosophy, table);
	}
	i = -1;
	while (++i < table->params.nb_philos)
		pthread_detach(philos_thread[i]);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	table = malloc(sizeof(t_philos_table));
	table->left_fork = malloc(sizeof(pthread_mutex_t));
	table->right_fork = malloc(sizeof(pthread_mutex_t));
	if (!struct_init(table, args))
		return ;
	table->params = args;
	philosophy_start(table);
}
