#include "philosophers.h"

t_philo **init_philos(t_philos_table *table)
{
	t_philo **philos;
	int i;

	i = -1;
	philos = malloc(sizeof (t_philo *) * (table->params.nb_philos + 1));
	if (!philos)
		return (NULL);
	philos[table->params.nb_philos] = NULL;
	while(++i < table->params.nb_philos)
	{
		philos[i] = malloc(sizeof (t_philo));
		if (philos[i] == NULL)
			return (free_ptrs((void **)philos, i), NULL);
		philos[i]->id = i + 1;
	}
	return (philos);
}

void distrubute_forks(t_philos_table **table)
{
	int i;

	i = -1;
	while(++i < table[0]->params.nb_philos)
	{
		table[0]->philos[i]->left_fork = (table)[0]->forks[i];
		table[0]->philos[i]->right_fork = (table)[0]->forks[(i + 1)\
		* ((table[0]->philos[i + 1] != NULL) + (table[0]->params.nb_philos == 1))];
	}
}
sem_t **semaphores_init(t_philos_table *table, t_philo **philo)
{
	sem_t	**forks;
	int		i;

	if (!philo)
		return NULL;
	forks = malloc(table->params.nb_philos  * sizeof(sem_t *));
	if(!forks)
		return NULL;
	i = -1;
	while(++i < table->params.nb_philos)
	{
		forks[i] = malloc(sizeof (t_philo *));
		if(!forks[i])
			return (free_ptrs((void **)forks, i), NULL);
	}
	return forks;
}

int init(t_philos_table **table, t_params arg)
{
	int condition;

	condition = 0;
	*table = malloc(sizeof(t_philos_table));
	if (!table)
		return 1;
	table[0]->params = arg;
    gettimeofday(&(*table)->start_time, NULL);
    (*table)->philos = init_philos(*table);
	(*table)->forks = semaphores_init(*table, (*table)->philos);
	distrubute_forks(table);
    condition = ((*table)->forks == NULL) + ((*table)->philos == NULL) + ((*table)->died == NULL);
    return condition;
}