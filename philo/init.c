#include "philosophers.h"


t_philo *init_philos(t_params arg)
{
    int i = 0;
    t_philo *philos;

    philos = malloc(sizeof(t_philo) * arg.nb_philos);
    philos->params = arg;
    if (!philos)
        return NULL;
    while (i < arg.nb_philos)
    {
        philos[i].id = i + 1;
        i++;
    }
    return NULL;
}

int init(t_philos_table *table, t_params arg)
{
    table = malloc(sizeof(t_philos_table));
    if(!table)
        return 1;
    table->params = arg;
    table->philos = init_philos(arg);
    if(!table->philos)
        return 1;
    return 0;
}