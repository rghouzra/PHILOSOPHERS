/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:48 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/05 21:57:31 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	philo_take_fork(t_philo *philo)
{
	if (philo->params.nb_philos > 1)
	{
		sem_wait(philo->fork);
		__lock_print("has taken a fork", philo->id, philo);
	}
	sem_wait(philo->fork);
	__lock_print("has taken a fork", philo->id, philo);
}

void	philo_eat(t_philo *philo)
{
	philo_take_fork(philo);
	if (philo->params.nb_philos > 1)
	{
		__lock_print("is eating", philo->id, philo);
		philo->eat_counter++;
		sem_post(philo->fork);
		gettimeofday(&philo->last_meal, NULL);
	}
	else
		philo->last_meal = (struct timeval){0, 0};
	sem_post(philo->fork);
	if (philo->eat_counter == philo->params.eat_count)
		exit(1);
	ft_usleep(philo->params.time_to_eat * 1000);
}

void	philo_sleep(t_philo *philo)
{
	__lock_print("is sleeping", philo->id, philo);
	ft_usleep(philo->params.time_to_sleep * 1000);
}

void	philo_think(t_philo *philo)
{
	__lock_print("is thinking", philo->id, philo);
}

void	*philosopher_routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2 == 0)
		ft_usleep(50);
	while (1)
	{
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
}
