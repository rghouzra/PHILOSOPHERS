#include "philosophers.h"

t_philo **init_philos(t_philos_table *table)
{
	t_philo **philos;
	int i;

	i = -1;
	philos = malloc(sizeof (t_philo *) * table->params.nb_philos);
	if (!philos)
		return (NULL);
	while(++i)
	{
		philos[i] = malloc(sizeof (t_philo));
		if()
	}
}

int init(t_philos_table **table, t_params arg)
{
	int condition;

	condition = 0;
    *table = malloc(sizeof(t_philos_table));
    if (!table)
        return 1;
    gettimeofday(&(*table)->start_time, NULL);
    (*table)->philos = init_philos(*table);
    condition = ((*table)->forks == NULL) + ((*table)->philos == NULL) + ((*table)->died == NULL);
    return condition;
}