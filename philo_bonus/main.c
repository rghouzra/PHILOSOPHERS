/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/01 15:04:13 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/05 22:00:18 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int	main(int ac, char **argv)
{
	t_params	params;

	if (ac < 5 || ac > 6)
		return (ft_putstr_fd("invalid nums of arguments\n", 2), 1);
	if (parsing(ac - 1, argv + 1, &params) != 1)
		return (ft_putstr_fd("invalid args", 2), 1);
	prepare_table(params);
	return (0);
}
