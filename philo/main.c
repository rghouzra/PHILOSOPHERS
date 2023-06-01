/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:04:48 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/01 15:04:49 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	main(int ac, char **argv)
{
	t_params		params;
	t_philos_table	*table;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("invalid nums of arguments\n", 2), 1);
	if (parsing(ac - 1, argv + 1, &params) != 1)
		return (ft_putstr_fd("invalid args", 2), 1);
	table = prepare_table(params);
	return (0);
}
