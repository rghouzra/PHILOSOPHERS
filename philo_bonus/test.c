#include <libc.h>
#include <semaphore.h>
#include <pthread.h>


int main(int ac, char **av)
{
	sem_t *semaphore;

	semaphore = malloc(sizeof(sem_t));
	// semaphore = sem_open
	sem_init(semaphore, );
}