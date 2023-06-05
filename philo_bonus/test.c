#include <pthread.h>
#include <stdio.h>

void *r(void *p)
{
	while(1)
		printf("c");
	return NULL;
}
int main()
{
	pthread_t a;
	pthread_create(&a, NULL, r,NULL);
	printf("%lld\n", a);
	pthread_detach(a);
	while(1);
}
