#include "philosophers.h"

long long get_time_in_ms(struct timeval time_par, int checker)
{
	long long   milliseconds;
    struct      timeval time;

    time = time_par;
    if (!checker)
        gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (milliseconds);
}


