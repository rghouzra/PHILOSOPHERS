#include "philosophers.h"

t_philo **init_philos(t_philos_table *table)
{
    int     i;
    t_philo **philos;

    i = -1;
    philos = malloc(sizeof(t_philo *) * (*table).params.nb_philos);
    if (!philos)
        return (NULL);
    //free philos if malloc fails inside the loop
    while (++i < (*table).params.nb_philos)
    {
        philos[i] = malloc(sizeof(t_philo));
        if (!philos[i])
            return ( NULL);
        gettimeofday(&philos[i]->last_meal, NULL);
        philos[i]->id = i + 1;
        philos[i]->eat_counter = 0;
        philos[i]->params = (*table).params;
        philos[i]->left_fork = (*table).forks[i];
        philos[i]->right_fork = (*table).forks[(i + 1)\
		* (((*table).forks[i + 1] != NULL) + ((*table).params.nb_philos == 1))];
        philos[i]->meal = (*table).meals[i];
        philos[i]->eat_count = (*table).eat_counts[i];
    }
    return philos;
}

void free_mutexes(pthread_mutex_t **ptr, int size)
{
    int i;

    i = -1;
    while (++i < size)
    {
        pthread_mutex_destroy(ptr[i]);
        free(ptr[i]);
    }
}

int protect_mutexes(t_philos_table *table)
{
    if(!(*table).forks || !(*table).meals || !(*table).eat_counts)
    {
        free_mutexes((*table).forks, (*table).params.nb_philos);
        free_mutexes((*table).meals, (*table).params.nb_philos);
        free_mutexes((*table).eat_counts, (*table).params.nb_philos);
        free((*table).forks);
        free((*table).meals);
        free((*table).eat_counts);
        (*table).forks = NULL;
        (*table).meals = NULL;
        (*table).eat_counts = NULL;
        return (1);
    }
    return (0);
}

void init_mutexes(t_philos_table *table)
{
    int i;

    i = -1;
    (*table).forks = malloc(sizeof(pthread_mutex_t *) * (*table).params.nb_philos);
    (*table).meals = malloc(sizeof(pthread_mutex_t *) * (*table).params.nb_philos);
    (*table).eat_counts = malloc(sizeof(pthread_mutex_t *) * (*table).params.nb_philos);
    if(protect_mutexes(table))
        return;
    while (++i < (*table).params.nb_philos)
    {
        (*table).forks[i] = malloc(sizeof(pthread_mutex_t));
        (*table).meals[i] = malloc(sizeof(pthread_mutex_t));
        (*table).eat_counts[i] = malloc(sizeof(pthread_mutex_t));
        pthread_mutex_init((*table).forks[i], NULL);
        pthread_mutex_init((*table).meals[i], NULL);
        pthread_mutex_init((*table).eat_counts[i], NULL);
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
    init_mutexes(*table);
    (*table)->philos = init_philos(*table);
    gettimeofday(&(*table)->start_time, NULL);
    condition = ((*table)->forks == NULL) + ((*table)->philos == NULL);
    return condition;
}