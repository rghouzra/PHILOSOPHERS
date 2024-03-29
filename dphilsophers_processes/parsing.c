/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:39:46 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/04 09:54:34 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	isvalid(char **s, int ac)
{
	int	i;
	int	j;
	int	flag;
	int	err_flag;

	i = -1;
	err_flag = 0;
	while (++i < ac)
	{
		j = -1;
		flag = 0;
		while (s[i][++j])
			flag += ft_isdigit(s[i][j]);
		err_flag += ((flag == j) * (j != 0));
	}
	return (err_flag == ac);
}

int	fill_params(char **av, int ac, t_params *params)
{
	long	*ptr;
	int		i;

	i = -1;
	ptr = (long *)params;
	while (++i < ac)
	{
		*ptr = ft_atoi(av[i]);
		if (*ptr++ > INT_MAX)
			return (0);
	}
	if (ac == 4)
		*ptr = -1;
	return (1);
}

int	parsing(int ac, char **av, t_params *params)
{
	if (!isvalid(av, ac))
		return (0);
	return (fill_params(av, ac, params));
}
