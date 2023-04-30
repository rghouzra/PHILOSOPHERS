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
		usleep(100);
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
	int i;
	t_philo_checker *checker;

	checker  = (t_philo_checker *)ptr;
	while (1)
	{
		i = -1;
		while(++i < checker->table->params.nb_philos)	
		{
			checker->current_time = get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(checker->table->philos[i]->start_time, 1);
			if (checker->current_time - (get_time_in_ms(checker->table->philos[i]->last_meal, 1) - get_time_in_ms(checker->table->philos[i]->start_time, 1))\
			 >= checker->table->params.time_to_die && get_time_in_ms(checker->table->philos[i]->last_meal, 1) != 0)
			{
				printf("%lld %d Died\n", checker->current_time, checker->table->philos[i]->id);
				pthread_mutex_lock(checker->death);
				*checker->table->philos[i]->died = 1;
				pthread_mutex_unlock(checker->death);
				return (NULL);
			}
			if (checker->table->philos[i]->eat_counter > checker->table->params.eat_count && checker->table->params.eat_count != -1)
			{
				printf("philos has reached the max");
				exit(1);
			}
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
		ft_usleep(250);
	i = 0;
	while(1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
		if (*philo->died || !philo->right_fork || !philo->left_fork)
			return (NULL);
	}
	return (NULL);
}

void init_checker_struct(t_philos_table *table, t_philo_checker **checker)
{
	*checker = malloc(sizeof(t_philo_checker));
	if(!checker)
		return ;
	(*checker)->death = malloc(sizeof(pthread_mutex_t));
	if(!(*checker)->death)
		return ;
	pthread_mutex_init((*checker)->death, NULL);
	(*checker)->table = table;
}

void philosophy_start(t_philos_table *table)
{
	int			i;
	t_philo		**philos;
	t_philo_checker *checker;

	i = -1;
	philos = table->philos;
	init_checker_struct(table, &checker);
	pthread_create(&checker->death_checker, NULL, philo_checker, checker);
	while (++i < table->params.nb_philos)
		pthread_create(&philos[i]->philo, NULL, philosophers_routine, philos[i]);
	i = -1;
	while (++i < table->params.nb_philos)
			pthread_join(philos[i]->philo, NULL);
	pthread_join(checker->death_checker, NULL);
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
