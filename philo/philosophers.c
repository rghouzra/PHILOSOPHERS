#include "philosophers.h"


void philo_take_fork(t_philo	*philo)
{
	printf("%d has taken fork\n" ,philo->id);
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
}

long get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(long time)
{
	long start;
	long end;

	start = get_time();
	end = start + time;
	while (get_time() < end)
		usleep(time);
}

void philo_eat(t_philo *philo)
{
	printf("%d eat\n", philo->id);
	ft_usleep(philo->params.time_to_eat );
}

void philo_sleep(t_philo *philo)
{
	gettimeofday(&philo->last_meal, NULL);
	printf("%d sleeping\n", philo->id);
	ft_usleep(philo->params.time_to_sleep);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void philo_think(t_philo *philo)
{
	printf("%d thinking\n", philo->id);
	ft_usleep(100);
}

void *philosophers_routine(void *param)
{
	t_philo *philo;
	long long i;

	philo = (t_philo *)param;
	i = 0;
	while(1)
	{
		philo_take_fork(philo);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}
/*
	?: suppose i have mutexes point to all mutexes which represent forks
	TODO FREE MEMORY ALLOCATION
*/

void *philo_checker(void *ptr)
 {
	t_philos_table *table;
	int i;
	long long timestamp_timetodie;
	long long timestamp_currtime;

	table = (t_philos_table *)ptr;
	while(1)
	{
		i = -1;
		timestamp_currtime = table->start_time.tv_sec * 1000 + table->start_time.tv_usec / 1000;
		timestamp_timetodie = timestamp_currtime 
		while(++i < table->params.nb_philos)
		{

		}
	}
	return (NULL);
 }
void philosophy_start(t_philos_table *table)
{
	int			i;
	t_philo 	**philos;
	pthread_t		death_checker;
	
	philos = table->philos;
	i = -1;

	pthread_create(&death_checker, NULL, philo_checker, table);
	while (++i < table->params.nb_philos)
	{
		philos[i]->left_fork = (table)->forks[i];
		philos[i]->right_fork = (table)->forks[(i + 1) * !(table->forks[i + 1] == NULL)];
		pthread_create(&philos[i]->philo, NULL, philosophers_routine, philos[i]);
	}
	print_philos_dot(philos, table->params.nb_philos);	
	pthread_join(death_checker, NULL);
	i = -1;
	while (++i < table->params.nb_philos)
		pthread_join(philos[i]->philo, NULL);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
