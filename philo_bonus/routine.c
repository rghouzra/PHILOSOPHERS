#include "philosophers.h"

void philo_take_fork(t_philo	*philo)
{
}

void philo_eat(t_philo *philo)
{

}

void philo_sleep(t_philo *philo)
{
	__lock_print("is sleeping", philo->id, philo);
	ft_usleep(philo->params.time_to_sleep);
}

void philo_think(t_philo *philo)
{
	__lock_print("is thinking", philo->id, philo);
	ft_usleep(200);
}