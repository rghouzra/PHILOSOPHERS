/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 14:39:46 by rghouzra          #+#    #+#             */
/*   Updated: 2022/12/18 14:39:48 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "philosophers.h"

int	isvalid(char **s, int ac)
{
	int	i;
	int	j;
	int	flag;
	int err_flag;

	i = -1;
	err_flag = 0;
	while (++i < ac)
	{
		j = -1;
		flag = 0;
		while (s[i][++j])
		{
			if (ft_isdigit(s[i][j]))
				flag ++;
		}
		err_flag += ((flag == j) * j != 0);
	}
	return (err_flag == ac);
}

int	parsing(int ac, char **av)
{
	if (!isvalid(av, ac))
		return 0;

	return (1);
}