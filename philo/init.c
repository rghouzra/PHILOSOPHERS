#include "philosophers.h"


t_philo **init_philos(t_params arg)
{
    int     i;
    t_philo **philos;

    i = -1;
    philos = malloc(sizeof(t_philo *) * arg.nb_philos);
    if (!philos)
        return (NULL);
    while (++i < arg.nb_philos)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            return (NULL);
        gettimeofday(&philos[i]->last_meal, NULL);
        philos[i]->id = i + 1;
    }
    return philos;
}



void init_mutexes(t_philos_table **table)
{
    int i;

    (*table)->forks = malloc(sizeof(pthread_mutex_t) * ((*table)->params.nb_philos + 1));
    if (!(*table)->forks)
        return ; 
    (*table)->forks[(*table)->params.nb_philos] = NULL;
    i = -1;
    while(++i < (*table)->params.nb_philos)
    {
        (*table)->forks[i] = malloc(sizeof(pthread_mutex_t));
        if (!(*table)->forks[i])
            free_mutexes((*table)->forks, (*table)->params.nb_philos);
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
    gettimeofday(&(*table)->start_time, NULL);
    init_mutexes(table);
    (*table)->philos = init_philos(arg);
    condition = ((*table)->forks == NULL) + ((*table)->philos == NULL);
    return condition;
}