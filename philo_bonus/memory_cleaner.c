/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_cleaner.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:04:17 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/04 09:32:11 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	free_ptrs(void **ptr, int size)
{
	int	i;

	i = -1;
	if (!ptr)
		return ;
	while (++i < size)
		free(ptr[i]);
	free(ptr);
	return ;
}
void	free_mutexes(t_philos_table *table)
{
}

void	sem_unlinker(void)
{
	sem_unlink("/forks");
	sem_unlink("/sem_print");
}