#include "philosophers.h"

void philo_take_fork(t_philo	*philo)
{	
	// fprintf(stderr, "lfork->%p\trfork->%p\n", philo->lfork, philo->rfork);
	if(philo->params.nb_philos > 1)
	{
		sem_wait(philo->lfork);
		__lock_print("has taken a fork", philo->id, philo);
	}
	sem_wait(philo->rfork);
	__lock_print("has taken a fork", philo->id, philo);
}

void philo_eat(t_philo *philo)
{
	philo_take_fork(philo);
	philo->last_meal = (struct timeval){0, 0};
	if(philo->params.nb_philos > 1)
	{
		__lock_print("is eating", philo->id, philo);
		gettimeofday(&philo->last_meal, NULL);
		philo->eat_counter++;
	}
	if(philo->params.nb_philos > 1)
		sem_post(philo->lfork);
	sem_post(philo->rfork);
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

void philosopher_routine(t_philo *philo)
{
	if(philo->id & 1)
		ft_usleep(200);
	while(1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	exit(0);
}