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

void __lock_print(char *str, int id, t_philo *philo)
{
	pthread_mutex_lock(philo->stat);
	if(*philo->died_ptr && ft_strcmp(str, "died"))
		return ;
	pthread_mutex_unlock(philo->stat);
	pthread_mutex_lock(philo->print);
	printf("%lld\t%d\t%s\n", get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->start_time, 1), id,str);
	pthread_mutex_unlock(philo->print);
}


void ft_usleep(long long time)
{
	long long start;

	start = get_time_in_ms((struct timeval){0, 0}, 0);
	while (get_time_in_ms((struct timeval){0, 0}, 0) - start < time)
		usleep(500);
}

int check_death(t_philos_table *table, int index)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	pthread_mutex_lock(table->philos[index]->meal);
	if (get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[index]->last_meal, 1) > table->params.time_to_die\
	&& table->philos[index]->last_meal.tv_sec != -1)
	{
		__lock_print("died", table->philos[index]->id, table->philos[index]);
		return (1);
	}
	pthread_mutex_unlock(table->philos[index]->meal);
	pthread_mutex_lock(table->philos[index]->eat_count);
	if((table->philos[index]->eat_counter >= table->params.eat_count && table->params.eat_count != -1))
	{
		pthread_mutex_unlock(table->philos[index]->eat_count);
		return (1);
	}
	pthread_mutex_unlock(table->philos[index]->eat_count);
	return (0);
}
