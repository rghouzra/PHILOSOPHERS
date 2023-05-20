#include "philosophers.h"

int check_death(t_philo *philo)
{
	if(philo->params.time_to_die < get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->last_meal, 1)\
	&& philo->last_meal.tv_sec != -1)
	{
		__lock_print("\033[0;31mis died", philo->id, philo);
		return 1;
	}
	return (0);
}

void  *death_checker(void *ptr)
{
	t_philo *philo;

	philo = (t_philo *)ptr;	
	while(1)
	{
		if (check_death(philo))
		{
			exit(0);
			return ((void *)0);
		}
	}
	return (NULL);
}

void init_checker_struct(t_philos_table *table, t_philo_checker **checker)
{
	*checker = malloc(sizeof(t_philo_checker));
	if (!checker)
		return ;
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
	while(++i < table->params.nb_philos)
	{
		philos[i]->pid = ft_fork();
		if (!philos[i]->pid)
		{
			pthread_create(&checker->death_checker, NULL, death_checker, philos[i]);
			philos[i]->start_time = table->start_time;
			philosopher_routine(philos[i]);
		}
 	}
	waitpid(-1, NULL, 0);
	for (i = 0; i < table->params.nb_philos; i++)
		kill(philos[i]->pid, SIGINT);
	sem_close(table->lfork);
	sem_close(table->print);
	sem_close(table->rfork);
	cleanup_processes();
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
