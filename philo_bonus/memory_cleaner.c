#include "philosophers.h"

void free_ptrs(void **ptr, int size)
{
  int i;

  i = -1;
  if (!ptr)
    return;
  while(++i < size)
    free(ptr[i]);
  free(ptr);
  return;
}
void free_mutexes(t_philos_table *table)
{

}
