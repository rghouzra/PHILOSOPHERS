#include "philosophers.h"


void philo_take_fork(t_philo	*philo)
{
		printf("%lld %d has taken a fork\n",  get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1),philo->id);
		pthread_mutex_lock(philo->right_fork);
		printf("%lld %d has taken a fork\n" , get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1),philo->id);
		pthread_mutex_lock(philo->left_fork);
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
		usleep(200);
}

void philo_eat(t_philo *philo)
{
		if(philo->right_fork == NULL || philo->left_fork == NULL)
			return ;
		philo_take_fork(philo);
		printf("%lld %d is eating\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1), philo->id);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_lock(philo->meal);
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(philo->meal);
		pthread_mutex_lock(philo->eat_count);
		// philo->eat_counter++;
		pthread_mutex_unlock(philo->eat_count);
		ft_usleep(philo->params.time_to_eat);
}

void philo_sleep(t_philo *philo)
{
	printf("%lld %d is sleeping\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1), philo->id);
	ft_usleep(philo->params.time_to_sleep);
}

void philo_think(t_philo *philo)
{
	printf("%lld %d is thinking\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(philo->start_time, 1), philo->id);
	ft_usleep(200);
}

void *philo_checker(void *ptr)
{
	t_philos_table *table;
	long long		curr_time;
	int				i;
	pthread_mutex_t *mutex;
	pthread_mutex_t *mutex2;

	mutex = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex, NULL);
	mutex2 = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex2, NULL);
	table  = (t_philos_table *)ptr;
	while(1)
	{
		i = -1;
		while(++i < table->params.nb_philos)	
		{
			curr_time = get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[i]->start_time, 1);
			pthread_mutex_lock(mutex);
			if (curr_time - get_time_in_ms(table->philos[i]->last_meal, 1) >= table->params.time_to_die && table->philos[i]->last_meal.tv_sec != -1)
			{
				printf("%lld %d Died\n", curr_time,table->philos[i]->id);
				*table->philos[i]->died = 1;
			}
			pthread_mutex_unlock(mutex);
			pthread_mutex_lock(mutex2);
			if (table->philos[i]->eat_counter > table->params.eat_count && table->params.eat_count != -1)
			{
				printf("philos has reached the max");
				exit(1);
			}
			pthread_mutex_unlock(mutex2);
		}
	}
	return (NULL);
}

void *philosophers_routine(void *param)
{
	t_philo		*philo;
	long long	i;

	philo = (t_philo *)param;
	if((philo->id & 1))
		ft_usleep(500);
	i = 0;
	while(1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if(*philo->died || !philo->right_fork)
			break;
	}
	return (NULL);
}

void philosophy_start(t_philos_table *table)
{
	int			i;
	t_philo		**philos;
	pthread_t	death_checker;

	i = -1;
	philos = table->philos;
	pthread_create(&death_checker, NULL, philo_checker, table);
	while (++i < table->params.nb_philos)
		pthread_create(&philos[i]->philo, NULL, philosophers_routine, philos[i]);
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
