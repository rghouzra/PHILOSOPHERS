#include "philosophers.h"

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
		__lock_print("died", table->philos[index]->id, table->philos[index]);
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
		if (check_death(checker->table, i))
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
	if((philo->id & 1) == 0)
		ft_usleep(100);
	while(1)
	{
		pthread_mutex_lock(philo->stat);
		cond = (*philo->died_ptr);
		pthread_mutex_unlock(philo->stat);
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
	table->checker_ptr = *checker;
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
	free_mutexes(table);
}
