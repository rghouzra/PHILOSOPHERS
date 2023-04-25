#include "philosophers.h"

t_philo **init_philos(t_philos_table *table)
{
    int     i;
    t_philo **philos;

    i = -1;
    philos = malloc(sizeof(t_philo *) * (*table).params.nb_philos);
    if (!philos)
        return (NULL);
    while (++i < (*table).params.nb_philos)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            return (NULL);
        gettimeofday(&philos[i]->last_meal, NULL);
        philos[i]->id = i + 1;
        philos[i]->eat_counter = 0;
        philos[i]->params = (*table).params;
        philos[i]->left_fork = (*table).forks[i];
        philos[i]->right_fork = (*table).forks[(i + 1)\
		* (((*table).forks[i + 1] != NULL) + ((*table).params.nb_philos == 1))];
    }
    return philos;
}

void init_mutexes(t_philos_table **table)
{
    int i;

    i = -1;
    (*table)->forks = malloc(sizeof(pthread_mutex_t) * ((*table)->params.nb_philos + 1));
    if (!(*table)->forks)
        return ; 
    (*table)->forks[(*table)->params.nb_philos] = NULL;
    while(++i < (*table)->params.nb_philos)
    {
        (*table)->forks[i] = malloc(sizeof(pthread_mutex_t));
        if (!(*table)->forks[i])
            free_mutexes((*table)->forks, (*table)->params.nb_philos);
        pthread_mutex_init((*table)->forks[i], NULL);
    }
}

int init(t_philos_table **table, t_params arg)
{
    int condition;

    condition = 0;
    *table = malloc(sizeof(t_philos_table));
    if (!table)
        return 1;
    (*table)->params = arg;
    init_mutexes(table);
    (*table)->philos = init_philos(*table);
    condition = ((*table)->forks == NULL) + ((*table)->philos == NULL);
    return condition;
}