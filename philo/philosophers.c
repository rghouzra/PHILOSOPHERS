#include "philosophers.h"

void __lock_print(char *str, int id,t_philo *philo);

void philo_take_fork(t_philo	*philo)
{
	pthread_mutex_lock(philo->right_fork);
	__lock_print("has taken a fork", philo->id, philo);
	pthread_mutex_lock(philo->left_fork);
	__lock_print("has taken a fork", philo->id, philo);
}

void __lock_print(char *str, int id, t_philo *philo)
{
	pthread_mutex_lock(philo->stat);
	if(philo->died_ptr && *philo->died_ptr)
		return ;
	pthread_mutex_unlock(philo->stat);
	printf("%lld    %d   %s\n", get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->start_time, 1), id,str);
}

void ft_usleep(long long time)
{
	long long start;

	start = get_time_in_ms((struct timeval){0, 0}, 0);
	while (get_time_in_ms((struct timeval){0, 0}, 0) - start < time)
		usleep(500);
}

void philo_eat(t_philo *philo)
{
		// if(philo->right_fork == NULL || philo->left_fork == NULL)
		// 	return ;
		philo_take_fork(philo);
		__lock_print("is eating", philo->id, philo);
		pthread_mutex_lock(philo->meal);
		gettimeofday(&philo->last_meal, NULL);
		pthread_mutex_unlock(philo->meal);
		ft_usleep(philo->params.time_to_eat);
		pthread_mutex_lock(philo->eat_count);
		philo->eat_counter++;
		pthread_mutex_unlock(philo->eat_count);
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
	ft_usleep(philo->params.time_to_sleep);
	__lock_print("is sleeping", philo->id, philo);
}

void philo_think(t_philo *philo)
{
	ft_usleep(200);
	__lock_print("is thinking", philo->id, philo);
}

long long get_diff_time(struct timeval start, struct timeval end)
{
	return ((end.tv_sec - start.tv_sec) * 1000 + (end.tv_usec - start.tv_usec) / 1000);
}

struct timeval get_time_of_day(void)
{
	struct timeval tv;

	gettimeofday(&tv, NULL);
	return (tv);
}

int check_death(t_philos_table *table, int index)
{
	struct timeval time;

	gettimeofday(&time, NULL);
	if (get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[index]->last_meal, 1) > table->params.time_to_die\
	&& table->philos[index]->last_meal.tv_sec != -1)
	{
		printf("\033[0;31m%lld %d died\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[index]->start_time, 1),\
		table->philos[index]->id);
		return (1);
	}
	pthread_mutex_lock(table->philos[index]->eat_count);
	if((table->philos[index]->eat_counter >= table->params.eat_count && table->params.eat_count != -1)\
	|| table->params.nb_philos == 1)
	{
		printf("\033[0;31m%lld %d died\n", get_time_in_ms((struct timeval){0, 0}, 0) - get_time_in_ms(table->philos[index]->start_time, 1),\
		table->philos[index]->id);
		return (1);
	}
	pthread_mutex_unlock(table->philos[index]->eat_count);
	return (0);
}

int  philo_checker(void *ptr)
{
	int i;
	t_philo_checker *checker;

	checker  = (t_philo_checker *)ptr;
	i = -1;
	while (++i < checker->table->params.nb_philos)	
	{
	    if(check_death(checker->table, i))
	    {
	        pthread_mutex_lock(checker->table->philos[i]->stat);
	        *checker->table->philos[i]->died_ptr = 1;
	        pthread_mutex_unlock(checker->table->philos[i]->stat);
	        return (0);
	    }
	}
	return (1);
}

void *philosophers_routine(void *param)
{
	t_philo		*philo;
	int cond;

	philo = (t_philo *)param;
	if((philo->id & 1))
		ft_usleep(100);
	while(1)
	{
		pthread_mutex_lock(philo->stat);
		cond = (*philo->died_ptr);
		pthread_mutex_unlock(philo->stat);
		cond += (philo->left_fork == NULL) || (philo->right_fork == NULL);
		if (cond)
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void init_checker_struct(t_philos_table *table, t_philo_checker **checker)
{
	*checker = malloc(sizeof(t_philo_checker));
	if (!checker)
		return ;
	(*checker)->death = malloc(sizeof(pthread_mutex_t));
	if (!(*checker)->death)
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
	gettimeofday(&table->start_time, NULL);
	philos = table->philos;
	init_checker_struct(table, &checker);
	while (++i < table->params.nb_philos)
		pthread_create(&philos[i]->philo, NULL, philosophers_routine, philos[i]);
	i = -1;
	while(1)
	{
		if (!philo_checker(checker))
		{
			while (++i < table->params.nb_philos)
				pthread_detach(philos[i]->philo);
			break;
		}
	}
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	*table->died = 0;
	philosophy_start(table);
}
