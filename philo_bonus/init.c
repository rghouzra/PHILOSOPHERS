#include "philosophers.h"

t_philo **init_philos(t_philos_table *table)
{
	t_philo **philos;
	int i;

	i = -1;
	philos = ft_malloc(sizeof (t_philo *) * (table->params.nb_philos + 1));
	philos[table->params.nb_philos] = NULL;
	while(++i < table->params.nb_philos)
	{
		philos[i] = ft_malloc(sizeof (t_philo));
		if (philos[i] == NULL)
			return (free_ptrs((void **)philos, i), NULL);
		philos[i]->id = i + 1;
		philos[i]->params = table->params;
		philos[i]->last_meal = (struct timeval){-1, -1};
		philos[i]->died = malloc(4);
		*philos[i]->died = 0;
	}
	return (philos);
}

void distrubute_forks(t_philos_table **table)
{
	int i;

	if(!table[0]->philos)
		return ;
	i = -1;
	while(++i < table[0]->params.nb_philos)
	{
		(*table)->philos[i]->fork = (*table)->forks;
		(*table)->philos[i]->print = (*table)->print;
	}
}

int		semaphores_init(t_philos_table **table)
{
	cleanup_processes();
	(*table)->forks = sem_open("/forks", O_CREAT, 0644 ,table[0]->params.nb_philos);
	if(table[0]->forks == SEM_FAILED)
		return (0);
	(*table)->print = sem_open("/sem_print", O_CREAT, 0644, 1);
	if(table[0]->print == SEM_FAILED)
		return (0);
	return 1;
}

int init(t_philos_table **table, t_params arg)
{
	int condition;

	condition = 0;
	*table = ft_malloc(sizeof(t_philos_table));
	if (!table)
		return 1;
	table[0]->params = arg;
	gettimeofday(&(*table)->start_time, NULL);
	(*table)->philos = init_philos(*table);
	if(!semaphores_init(table))
		;
	condition += semaphores_init(table);
	distrubute_forks(table);
	condition = ((*table)->forks == NULL) + ((*table)->philos == NULL);
	return (condition);
}