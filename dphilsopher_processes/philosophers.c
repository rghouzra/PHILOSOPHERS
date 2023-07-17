/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:03:53 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/07 09:28:48 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	process_routine(t_philo *philo, t_philos_table *table)
{
	t_philo_checker	*checker;

	init_checker_struct(table, &checker);
	if (!checker)
		return ;
	pthread_create(&checker->death_checker, NULL, death_checker_th, philo);
	philosopher_routine(philo);
	exit(1);
}

void	cleanup_after_termination(t_philos_table *table)
{
	int	i;

	i = -1;
	while (++i < table->params.nb_philos)
		kill(table->philos[i]->pid, SIGTERM);
	sem_close(table->forks);
	sem_close(table->print);
	sem_unlinker();
}

void	philosophy_start(t_philos_table *table)
{
	int		i;
	int		exit_status;

	exit_status = -1;
	i = -1;
	while (++i < table->params.nb_philos)
	{
		table->philos[i]->start_time = table->start_time;
		table->philos[i]->pid = ft_fork();
		if (table->philos[i]->pid == 0)
			process_routine(table->philos[i], table);
	}
	while (waitpid(-1, &exit_status, 0) != 0)
	{
		if (WEXITSTATUS(exit_status) == 1)
			break ;
		else if (exit_status == 0){
			break ;
		}
	}
	cleanup_after_termination(table);
}

t_philos_table	*prepare_table(t_params args)
{
	t_philos_table	*table;

	if (init(&table, args))
		return (NULL);
	philosophy_start(table);
	return (table);
}
