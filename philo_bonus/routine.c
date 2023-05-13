#include "philosophers.h"

void philo_take_fork(t_philo	*philo)
{
	__lock_print("has taken a fork", philo->id, philo);
	__lock_print("has taken a fork", philo->id, philo);
}

void philo_eat(t_philo *philo)
{
	__lock_print("is eating", philo->id, philo);
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
	for(int i = 0; i < 100; i++)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	exit(0);
}