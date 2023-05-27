#include "philosophers.h"

void philo_take_fork(t_philo	*philo)
{	
	//fprintf(stderr, "nb->%ld\n", philo->params.nb_philos);
	if(philo->params.nb_philos > 1)
	{
		sem_wait(philo->fork);
		__lock_print("has taken a fork", philo->id, philo);
	}
	sem_wait(philo->fork);
	__lock_print("has taken a fork", philo->id, philo);
}

void philo_eat(t_philo *philo)
{
	philo_take_fork(philo);
	// philo->last_meal = (struct timeval){0, 0};
	if(philo->params.nb_philos > 1)
	{
		gettimeofday(&philo->last_meal, NULL);
		// philo->eat_counter++;
	}
	__lock_print("is eating", philo->id, philo);
	if(philo->params.nb_philos > 1)
		sem_post(philo->fork);
	sem_post(philo->fork);
	ft_usleep(philo->params.time_to_eat);
}

void philo_sleep(t_philo *philo)
{
	__lock_print("is sleeping", philo->id, philo);
	ft_usleep(philo->params.time_to_sleep);
}

void philo_think(t_philo *philo)
{
	__lock_print("is thinking", philo->id, philo);
}

void *philosopher_routine(void *ptr)
{
	t_philo *philo;
	
	philo = (t_philo *)ptr;
	while(1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	exit(0);
}