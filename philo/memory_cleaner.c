#include "philosophers.h"

void free_ptrs(void **ptr, int size)
{
  int i;

  (void)size;
  i = -1;
  if (!ptr)
    return;
  while(ptr[++i])
    free(ptr[i]);
  free(ptr);
  return;
}
void free_mutexes(t_philos_table *table)
{
    int i;

    i = -1;
    while (++i < (*table).params.nb_philos)
    {
        pthread_mutex_destroy((*table).forks[i]);
        pthread_mutex_destroy((*table).meals[i]);
        pthread_mutex_destroy((*table).eat_counts[i]);
        free((*table).forks[i]);
        free((*table).meals[i]);
        free((*table).eat_counts[i]);
    }
    free((*table).forks);
    free((*table).meals);
    free((*table).eat_counts);
    (*table).forks = NULL;
    (*table).meals = NULL;
    (*table).eat_counts = NULL;
}
