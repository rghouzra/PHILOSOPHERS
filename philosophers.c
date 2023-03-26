#include "philosophers.h"

struct mutex
{
	int p;
	pthread_mutex_t x;
};
void *func1(void *arg)
{
	struct mutex *x = (struct mutex*)arg;

	int n = 50000;
	pthread_mutex_lock(&x->x);
	while(n--)
		x->p = x->p + 1;
	pthread_mutex_unlock(&x->x);
	return NULL;
}

void *func2(void *arg)
{
	struct mutex *x = (struct mutex*)arg;
	int n = 50000;
	pthread_mutex_lock(&x->x);
	while(n--)
		x->p = x->p + 1;
	pthread_mutex_unlock(&x->x);
	return NULL;
}



void	philosophy_start(t_params args)
{
	pthread_t thread[2];
	struct mutex x;
	x.p = 0;
	pthread_mutex_init(&x.x, NULL);
	pthread_create(&thread[0], NULL, func1, &x);
	pthread_create(&thread[1], NULL, func2, &x);
	pthread_join(thread[0], NULL);
	pthread_join(thread[1], NULL);
	pthread_mutex_destroy(&x.x);
	printf("%d\n", x.p);
}
