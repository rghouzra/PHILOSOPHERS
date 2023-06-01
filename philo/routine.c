/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:05:17 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/01 15:05:18 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void philo_take_fork(t_philo	*philo)
{
	if(philo->id & 1)
	{
		if (philo->right_fork)
		{
			__lock_print("has taken a fork", philo->id, philo);
			pthread_mutex_lock(philo->right_fork);
		}
		__lock_print("has taken a fork", philo->id, philo);
		pthread_mutex_lock(philo->left_fork);
	}
	else
	{
		if (philo->left_fork)
		{
			__lock_print("has taken a fork", philo->id, philo);
			pthread_mutex_lock(philo->left_fork);
		}
		if (philo->right_fork)
		{
			__lock_print("has taken a fork", philo->id, philo);
			pthread_mutex_lock(philo->right_fork);
		}
	}
}

void philo_eat(t_philo *philo)
{
		philo_take_fork(philo);
		if (philo->right_fork)
			__lock_print("is eating", philo->id, philo);
		pthread_mutex_lock(philo->meal);
		gettimeofday(&philo->last_meal, NULL);
		if (philo->right_fork == NULL)
			philo->last_meal.tv_sec = 0;
		pthread_mutex_unlock(philo->meal);
		pthread_mutex_lock(philo->eat_count);
		philo->eat_counter  += (philo->eat_counter == -1) + 1;
		pthread_mutex_unlock(philo->eat_count);
		ft_usleep(philo->params.time_to_eat);
		if(philo->left_fork)
			pthread_mutex_unlock(philo->left_fork);
		if(philo->right_fork)
			pthread_mutex_unlock(philo->right_fork);
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