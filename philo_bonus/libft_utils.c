/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rghouzra <rghouzra@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 06:00:28 by rghouzra          #+#    #+#             */
/*   Updated: 2023/06/01 14:18:51 by rghouzra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	if (!s1 || !s2)
		return (-1);
	while (*(s1 + i) && *(s2 + i) && *(s1 + i) == *(s2 + i))
		i++;
	return (*(s1 + i) - *(s2 + i));
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (*(s + i))
		i++;
	return (i);
}

int ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

long	ft_atoi(const char *nptr)
{
	int		sign;
	int		i;
	long	n;

	n = 0;
	i = 0;
	sign = 1;
	while ((*(nptr + i) >= 9 && *(nptr + i) <= 13) || *(nptr + i) == ' ')
			i++;
	if (*(nptr + i) == '+' || *(nptr + i) == '-')
	{
		if (*(nptr + i) == '-')
				sign = -1;
		i++;
	}
	while (ft_isdigit(*(nptr + i)) && *(nptr + i))
	{
		n *= 10;
		if (n <= -2147483648 || n >= 2147483647)
			return (2147483649);
		n += *(nptr + i) - 48;
		i++;
	}
	return (n * sign);
}