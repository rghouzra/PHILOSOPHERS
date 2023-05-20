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
		(*table)->philos[i]->lfork = (*table)->lfork;
		(*table)->philos[i]->rfork = (*table)->rfork;
		(*table)->philos[i]->print = (*table)->print;
	}
}

int		semaphores_init(t_philos_table **table)
{
	cleanup_processes();
	(*table)->lfork = sem_open("/f_sem", O_CREAT, 0644 ,table[0]->params.nb_philos);
	(*table)->rfork = NULL;
	if(table[0]->lfork == SEM_FAILED)
		return (0);
	if(table[0]->params.nb_philos > 1)
	{
		table[0]->rfork = sem_open("/s_sem", O_CREAT, 0644, table[0]->params.nb_philos);
		if(table[0]->rfork == SEM_FAILED)
			return (0);
	}
	(*table)->print = sem_open("/t_sem", O_CREAT, 0644, table[0]->params.nb_philos);
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
	condition = ((*table)->lfork == NULL) + ((*table)->rfork == NULL)\
	+ ((*table)->philos == NULL);
	return (condition);
}