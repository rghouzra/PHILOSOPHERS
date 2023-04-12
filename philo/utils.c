#include "philosophers.h"

long long get_time_in_ms(struct timeval time)
{
	long long milliseconds;

	milliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (milliseconds);
}


int main() {

    long long lastMealTimestamp = 1681335899721;


    int timeToDieInSeconds = 200;


    struct timeval currentTime;
    gettimeofday(&currentTime, NULL);
    long long currentTimestamp = currentTime.tv_sec * 1000LL + currentTime.tv_usec / 1000LL;


    long long timeToDieTimestamp = currentTimestamp + (long long)timeToDieInSeconds * 1000LL;
    long long durationMilliseconds = timeToDieTimestamp - lastMealTimestamp;

    printf("Duration until death: %lld ms\n", durationMilliseconds);

    return 0;
}
