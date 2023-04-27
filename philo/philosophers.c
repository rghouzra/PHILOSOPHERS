#include "philosophers.h"


void philo_take_fork(t_philo	*philo)
{
	printf("%d has taken fork\n" ,philo->id);
	if (philo->left_fork && philo->right_fork)
	{
		pthread_mutex_lock(philo->right_fork);
		pthread_mutex_lock(philo->left_fork);
	}
}

long long get_time(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void ft_usleep(long long time)
{
	long long start;

	start = get_time();
	while (get_time() - start < time)
		usleep(time );
}

void philo_eat(t_philo *philo)
{
	printf("%d eating\n", philo->id);
	philo->eat_counter = philo->eat_counter + 1;
	if(philo->left_fork && philo->right_fork)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
	}
	ft_usleep(philo->params.time_to_eat);
}

void philo_sleep(t_philo *philo)
{
	gettimeofday(&philo->last_meal, NULL);
	printf("%d sleeping\n", philo->id);
	ft_usleep(philo->params.time_to_sleep);
}

void philo_think(t_philo *philo)
{
	printf("%d thinking\n", philo->id);
	ft_usleep(200);
}

/*
	?: suppose i have mutexes point to all mutexes which represent forks

*/
	//TODO FREE MEMORY ALLOCATION

void *philo_checker(void *ptr)
{
	t_philos_table *table;
	long long		curr_time;
	int				i;

	table  = (t_philos_table *)ptr;
	while(1)
	{
		// i = -1;
		// curr_time = get_time_in_ms((struct timeval){0, 0}, 0);
		// while(++i < table->params.nb_philos)	
		// {
		// 	if(curr_time - get_time_in_ms(table->philos[i]->last_meal, 1) >= table->params.time_to_die)
		// 	{
		// 		printf("%lld %d Died\n", curr_time,table->philos[i]->id);
		// 		exit(1);
		// 	}
		// 	if (table->philos[i]->eat_counter > table->params.eat_count && table->params.eat_count != -1)
		// 	{
		// 		printf("philos has reached the max");
		// 		exit(1);
		// 	}
		// }
		// sleep(1);
	}
	return (NULL);
}

void *philosophers_routine(void *param)
{
	t_philo		*philo;
	long long	i;

	philo = (t_philo *)param;
	if(!(philo->id % 2))
		ft_usleep(200);
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

void philosophy_start(t_philos_table *table)
{
	int			i;
	t_philo		**philos;
	pthread_t	death_checker;

	philos = table->philos;
	i = -1;
	pthread_create(&death_checker, NULL, philo_checker, table);
	while (++i < table->params.nb_philos)
		pthread_create(&philos[i]->philo, NULL, philosophers_routine, philos[i]);
	pthread_join(death_checker, NULL);
	i = -1;
	while (++i < table->params.nb_philos)
		pthread_detach(philos[i]->philo);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
