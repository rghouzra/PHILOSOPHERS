#include "philosophers.h"

int check_death(t_philo *philo)
{
	 fprintf(stderr, "id->%d\tdif=%lld\n", philo->id,(get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->last_meal, 1)));

	if(philo->params.time_to_die < (get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->last_meal, 1))\
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
			exit(1);
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
	
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
