/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:53 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/05 13:17:54 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	process_routine(t_philo *philo, t_philos_table *table)
{
	t_philo_checker	*checker;
	int				i;

	i = -1;
	init_checker_struct(table, &checker);
	if (!checker)
		return ;
	pthread_create(&checker->death_checker, NULL, death_checker_th, philo);
	// pthread_detach(checker->death_checker);
	philosopher_routine(philo);
	exit(1);
}

void	philosophy_start(t_philos_table *table)
{
	int		i;
	t_philo	**philos;
	int		exit_status;

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
	while (waitpid(-1, &exit_status, 0) != 0)
	{
		if (exit_status)
			break ;
	}
	i = -1;
	while (++i < table->params.nb_philos)
		kill(table->philos[i]->pid, SIGTERM);
	sem_close(table->forks);
	sem_close(table->print);
	sem_unlinker();
}

void	prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return ;
	philosophy_start(table);
}
