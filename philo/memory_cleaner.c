#include "philosophers.h"

void free_mutexes(pthread_mutex_t **ptr, int size)
{
    int i;

    i = -1;
    while (++i)
        free(ptr[i]);
    free(ptr);
}
