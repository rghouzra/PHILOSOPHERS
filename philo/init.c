#include "philosophers.h"

void init_philo_mutexes(t_philo *philo, t_philos_table *table, int i)
{ 
    philo->left_fork = (*table).forks[i];

    philo->meal = (*table).meals[i];
    philo->eat_count = (*table).eat_counts[i];
}

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
            return ( NULL);
        gettimeofday(&philos[i]->start_time, NULL);
        philos[i]->last_meal = (struct timeval){0, 0};
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
    if(!(*table).forks || !(*table).meals || !(*table).eat_counts || !(*table).stats)
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
    (*table).forks = malloc(sizeof(pthread_mutex_t *) * ((*table).params.nb_philos + 1));
    (*table).meals = malloc(sizeof(pthread_mutex_t *) * (*table).params.nb_philos);
    (*table).eat_counts = malloc(sizeof(pthread_mutex_t *) * (*table).params.nb_philos);
    (*table).stats = malloc(sizeof(pthread_mutex_t *) * (*table).params.nb_philos);
    if(protect_mutexes(table))
        return;
	(*table).forks[(*table).params.nb_philos] = NULL;
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

void init_philos_stat(t_philos_table *table)
{
    int i;

    i = -1;
    table->philos_stat = malloc(sizeof(int) * table->params.nb_philos);
    if(!table->philos_stat)
        return;
    while (++i < table->params.nb_philos)
    {
        table->philos_stat[i] = 0;
        table->philos[i]->died = &table->philos_stat[i];
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
    gettimeofday(&(*table)->start_time, NULL);
    (*table)->philos = init_philos(*table);
    condition = ((*table)->forks == NULL) + ((*table)->philos == NULL);
    init_philos_stat(*table);
    return condition;
}