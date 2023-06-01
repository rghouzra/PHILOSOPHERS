/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:04:44 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/01 15:04:45 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init_philo_mutexes(t_philo **philo, t_philos_table *table, int i)
{ 
    (*philo)->left_fork = (*table).forks[i];
    (*philo)->right_fork = (*table).forks[(i + 1)\
    * (((*table).forks[i + 1] != NULL) + ((*table).params.nb_philos == 1))];
    (*philo)->meal = (*table).meals[i];
    (*philo)->eat_count = (*table).eat_counts[i];
    (*philo)->stat = (*table).stats;
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
            return (free_ptrs((void **)philos, i), NULL);
		gettimeofday(&philos[i]->start_time, NULL);
		philos[i]->last_meal = (struct timeval){-1, -1};
        philos[i]->id = i + 1;
        philos[i]->died_ptr = (*table).died;
        philos[i]->print = (*table).print;
        philos[i]->eat_counter = 0;
        philos[i]->params = (*table).params;
        init_philo_mutexes(&philos[i], table, i);
    }
    return philos;
}

// void free_mutexes(pthread_mutex_t **ptr, int size)
// {
//     int i;

//     i = -1;
//     while (++i < size)
//     {
//         pthread_mutex_destroy(ptr[i]);
//         free(ptr[i]);
//     }
// }

int protect_mutexes(t_philos_table *table)
{
    if(!(*table).forks || !(*table).meals\
	|| !(*table).eat_counts || !(*table).stats)
    {
        // free_mutexes((*table).forks, (*table).params.nb_philos);
        // free_mutexes((*table).meals, (*table).params.nb_philos);
        // free_mutexes((*table).eat_counts, (*table).params.nb_philos);
        // free((*table).forks);
        // free((*table).meals);
        // free((*table).eat_counts);
        // (*table).forks = NULL;
        // (*table).meals = NULL;
        // (*table).eat_counts = NULL;
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
    (*table).stats = malloc(sizeof(pthread_mutex_t));
    (*table).print = malloc(sizeof(pthread_mutex_t));
    if(protect_mutexes(table))
        return;
	(*table).forks[(*table).params.nb_philos] = NULL;
    pthread_mutex_init((*table).stats, NULL);
    pthread_mutex_init((*table).print, NULL);
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
	(*table)->died = malloc(sizeof(int));
	init_mutexes(*table);
	gettimeofday(&(*table)->start_time, NULL);
	(*table)->philos = init_philos(*table);
	condition = ((*table)->forks == NULL) + ((*table)->philos == NULL) + ((*table)->died == NULL);
	return condition;
}
