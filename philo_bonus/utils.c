#include "philosophers.h"

struct timeval get_timeval()
{
	struct timeval time;

	gettimeofday(&time, NULL);
	return time;
}
long long get_curr_time(t_philos_table *table, struct timeval time)
{
	return get_time_in_ms(time, 1) - get_time_in_ms(table->start_time, 1);
}
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

void __lock_print(char *str, int id, t_philo *philo)
{
	// if(*philo->died_ptr)
	// 	return ;
	printf("%lld\t%d\t%s\n", get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->start_time, 1), id,str);
}


void ft_usleep(long long time)
{
	long long start;

	start = get_time_in_ms((struct timeval){0, 0}, 0);
	while (get_time_in_ms((struct timeval){0, 0}, 0) - start < time)
		usleep(500);
}

void cleanup_processes()
{
	sem_unlink("/f_sem");
	sem_unlink("/s_sem");
}