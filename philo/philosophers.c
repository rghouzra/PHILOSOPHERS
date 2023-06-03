/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:05:01 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/03 10:46:07 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	philo_checker(void *ptr)
{
	int				i;
	t_philo_checker	*checker;

	checker = (t_philo_checker *)ptr;
	i = -1;
	while (++i < checker->table->params.nb_philos)
	{
		if (check_death(checker->table, i))
		{
			pthread_mutex_lock(checker->table->philos[i]->stat);
			*checker->table->philos[i]->died_ptr = 1;
			pthread_mutex_unlock(checker->table->philos[i]->stat);
			return (0);
		}
	}
	return (1);
}

void	*philosophers_routine(void *param)
{
	t_philo	*philo;
	int		cond;

	philo = (t_philo *)param;
	while (1)
	{
		pthread_mutex_lock(philo->stat);
		cond = (*philo->died_ptr);
		pthread_mutex_unlock(philo->stat);
		if (cond)
			return (NULL);
		philo_eat(philo);
		philo_sleep(philo);
		philo_think(philo);
	}
	return (NULL);
}

void	init_checker_struct(t_philos_table *table, t_philo_checker **checker)
{
	*checker = malloc(sizeof(t_philo_checker));
	if (!checker)
		return ;
	(*checker)->death = malloc(sizeof(pthread_mutex_t));
	if (!(*checker)->death)
		return ;
	pthread_mutex_init((*checker)->death, NULL);
	(*checker)->table = table;
	table->checker_ptr = *checker;
}

void	philosophy_start(t_philos_table *table)
{
	int				i;
	t_philo			**philos;
	t_philo_checker	*checker;

	i = -1;
	gettimeofday(&table->start_time, NULL);
	philos = table->philos;
	init_checker_struct(table, &checker);
	while (++i < table->params.nb_philos)
		pthread_create(&philos[i]->philo,
						NULL,
						philosophers_routine,
						philos[i]);
	i = -1;
	while (1)
	{
		if (!philo_checker(checker))
		{
			while (++i < table->params.nb_philos)
				pthread_detach(philos[i]->philo);
			break ;
		}
	}
	free(checker->death);
	free(checker);
}

t_philos_table	*prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return NULL;
	*table->died = 0;
	philosophy_start(table);
	free_mutexes(table);
	delete_garbage(&table);
	return table;
}
