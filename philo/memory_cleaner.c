/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:04:53 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/05 10:43:37 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_ptrs(void **ptr, int size)
{
	int	i;

	(void)size;
	i = -1;
	if (!ptr)
		return ;
	while (ptr[++i])
		free(ptr[i]);
	free(ptr);
	return ;
}

void	delete_garbage(t_philos_table **table)
{
	int	i;

	i = -1;
	if (!table || !*table)
		return ;
	ft_usleep(table[0]->params.time_to_die + table[0]->params.time_to_sleep
		+ table[0]->params.time_to_eat + 200);
	while (++i < table[0]->params.nb_philos)
		free(table[0]->philos[i]);
	free(table[0]->philos);
	free(table[0]->died);
	free(*table);
}

void	free_mutexes(pthread_mutex_t **ptr, int size)
{
	int	i;

	i = -1;
	while (++i < size)
	{
		pthread_mutex_destroy(ptr[i]);
		free(ptr[i]);
	}
}
