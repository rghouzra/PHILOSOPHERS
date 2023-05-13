#include "philosophers.h"

int check_death(t_philos_table *table, int index)
{
	struct timeval time;

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
			*checker->table->philos[i]->died_ptr = 1;
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
	
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
