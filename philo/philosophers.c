#include "philosophers.h"

int struct_init(t_philos_table *table, t_params arg)
{
	if(!table)
		return 0;
	pthread_mutex_init(table->left_fork, NULL);
	pthread_mutex_init(table->right_fork, NULL);
	if(!table->philos)
		return 0;
	return 1;
}

void philo_take_fork(t_philo *philo)
{
	printf("philo id %d take fork\n", philo->id);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

void philo_eat(t_philo *philo)
{
	printf("philo id %d eat\n", philo->philos->id);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void ft_usleep(unsigned int microseconds) {
    struct timeval start_time;
    gettimeofday(&start_time, NULL);

    unsigned int end_time_us = start_time.tv_usec + microseconds;
    time_t end_time_s = start_time.tv_sec + (end_time_us / 1000000);
    end_time_us %= 1000000;

    while (1) {
        struct timeval current_time;
        gettimeofday(&current_time, NULL);
        if (current_time.tv_sec > end_time_s ||
            (current_time.tv_sec == end_time_s && current_time.tv_usec >= end_time_us)) {
            break;
        }
    }
}

void philo_sleep(t_philos_table *philo)
{
	printf("philo id %d sleeping\n", philo->philos->id);
	ft_usleep(philo->params.time_to_sleep);
}

void *philosophy(void *philosopher)
{
	t_philo *philo;

	philo = (t_philo *)philosopher;
	while(1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

void philosophy_start(t_philos_table *table)
{
	int			i;

	i = -1;
	while (++i < table->params.nb_philos)
		pthread_create(&table->philos[i], NULL, philosophy, &table->philos[i]);
	i = -1;
	while (++i < table->params.nb_philos)
		pthread_join(table->philos[i], NULL);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(table, args))
		return ;
	philosophy_start(table);
}
