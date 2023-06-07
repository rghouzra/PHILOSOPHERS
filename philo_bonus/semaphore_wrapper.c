/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semaphore_wrapper.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/06 11:20:40 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/06 11:28:27 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_sem_close(sem_t *sem)
{
	int	ret;

	ret = sem_close(sem);
	if (ret != 0)
	{
		ft_putstr_fd("ft_sem_close", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_sem_wait(sem_t *sem)
{
	int	ret;

	ret = sem_wait(sem);
	if (ret != 0)
	{
		ft_putstr_fd("ft_sem_close", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_sem_post(sem_t *sem)
{
	int	ret;

	ret = sem_post(sem);
	if (ret != 0)
	{
		ft_putstr_fd("ft_sem_close", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}

int	ft_sem_unlink(const char *name)
{
	int	ret;

	ret = sem_unlink(name);
	if (ret != 0)
	{
		ft_putstr_fd("ft_sem_unlink", 2);
		exit(EXIT_FAILURE);
	}
	return (ret);
}
