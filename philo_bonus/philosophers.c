#include "philosophers.h"

int check_death(t_philos_table *table, int index)
{
	if(get_curr_time(table, table->philos[index]->last_meal) >= get_curr_time(table, get_timeval())\
	&& table->philos[index]->last_meal.tv_sec != -1)
	{
		__lock_print("is died", index + 1, table->philos[index]);
		return 1;
	}
	return (0);
}

int death_checker(t_philo_checker *checker)
{
	int i;

	i = -1;
	while (++i < checker->table->params.nb_philos)	
	{
		if (check_death(checker->table, i))
		{
			i = -1;
			while(++i < checker->table->params.nb_philos)
				kill(checker->table->philos[i]->pid, SIGTERM);
			return (0);
		}
	}
	return (1);
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
			philos[i]->start_time = table->start_time;
			philosopher_routine(philos[i]);
		}
 	}
	while(death_checker(checker) != 0)
		;
	while(wait(NULL) != -1)
		;
	sem_close(table->lfork);
	sem_close(table->rfork);
	sem_unlink("/f_sem");
	sem_unlink("/s_sem");
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
