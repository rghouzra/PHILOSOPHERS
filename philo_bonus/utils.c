/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:59 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/04 14:08:24 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	if (philo->params.time_to_die <= (get_time_in_ms((struct timeval){0, 0}, 0)
			- get_time_in_ms(philo->last_meal, 1)) && philo->last_meal.tv_sec !=
		-1)
	{
		*philo->died = 1;
		__lock_print("is died", philo->id, philo);
		return (1);
	}
	return (0);
}

int	death_checker(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	return (check_death(philo));
}

void	*death_checker_th(void *philo)
{
	while (1)
	{
		if (check_death(philo))
			return (NULL);
	}
	return (NULL);
}

long long	get_time_in_ms(struct timeval time_par, int checker)
{
	long long		milliseconds;
	struct timeval	time;

	time = time_par;
	if (!checker)
		gettimeofday(&time, NULL);
	milliseconds = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (milliseconds);
}

void	__lock_print(char *str, int id, t_philo *philo)
{
	sem_wait(philo->print);
	printf("%lld\t%d\t%s\n", get_time_in_ms((struct timeval){0, 0}, 0)
			- get_time_in_ms(philo->start_time, 1), id, str);
	if (ft_strcmp(str, "is died"))
		sem_post(philo->print);
}
