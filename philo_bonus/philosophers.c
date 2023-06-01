/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:53 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/01 15:03:54 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_death(t_philo *philo)
{
	// fprintf(stderr, "diff->%lld\n", get_time_in_ms(philo->last_meal, 1));
	if(philo->params.time_to_die < (get_time_in_ms((struct timeval){0, 0}, 0)\
	- get_time_in_ms(philo->last_meal, 1))\
	&& philo->last_meal.tv_sec != -1)
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

void	init_checker_struct(t_philos_table *table, t_philo_checker **checker)
{
	*checker = malloc(sizeof(t_philo_checker));
	if (!checker)
		return ;
	(*checker)->table = table;
}

void *death_checker_th(void *philo)
{
	while(1)
	{
		if(check_death(philo))
			return (exit(1), NULL);
	}
	return (NULL);
}
void	process_routine(t_philo *philo, t_philos_table *table)
{
	t_philo_checker	*checker;

	init_checker_struct(table, &checker);
	if (!checker)
		return ;	
	pthread_create(&checker->death_checker, NULL, death_checker_th, philo);
	pthread_detach(checker->death_checker);
	philosopher_routine(philo);
	exit(0);
}

void	philosophy_start(t_philos_table *table)
{
	int		i;
	t_philo	**philos;
	int exit_status;

	exit_status = 0;
	i = -1;
	gettimeofday(&table->start_time, NULL);
	philos = table->philos;
	while (++i < table->params.nb_philos)
	{
		philos[i]->start_time = table->start_time;
		philos[i]->pid = ft_fork();
		if (philos[i]->pid == 0)
			process_routine(philos[i], table);
	}
	while(waitpid(-1, &exit_status, 0) != 0)
	{
		if(exit_status)
			break;
	}
	i = -1;
	while(++i < table->params.nb_philos)
		kill(table->philos[i]->pid, SIGTERM);
	sem_close(table->forks);
	sem_close(table->print);
	cleanup_processes();
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
