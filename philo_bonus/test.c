#include <libc.h>
#include <semaphore.h>
#include <pthread.h>

struct s
{
	int i;
	sem_t sem;
};

void *routine(void *ptr)
{
	struct s p = *(struct s *)ptr;
	// int *p = (int *)ptr;
	sem_wait(&p.sem);
	printf("hello\t\n");
	sem_post(&p.sem);
	return NULL;
}

int main(int ac, char **av)
{
    pthread_t t[5];
	struct s p;
	// sem_init(&p.sem, 0, 1);
    for (size_t i = 0; i < 5; i++)
        pthread_create(&t[i], NULL, routine, (void *)&p);
    for (size_t i = 0; i < 5; i++)
		pthread_join(t[i], NULL);
	sem_destroy(&p.sem);
	// sem_destroy(&semapzhore);
}