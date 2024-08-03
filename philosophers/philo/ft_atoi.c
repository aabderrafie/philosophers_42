/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 19:44:52 by aaskal            #+#    #+#             */
/*   Updated: 2024/06/10 16:02:21 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	calculate_number(const char *str, int sign)
{
	long long	tmp;
	long long	res;
	int			i;

	i = 0;
	res = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		tmp = res;
		res = res * 10 + str[i] - '0';
		if (tmp != res / 10)
		{
			if (sign == -1)
				return (0);
			return (-1);
		}
		i++;
	}
	if (res * sign > INT_MAX || res * sign < INT_MIN)
	{
		printf("Error: Number is too big or too small\n");
		return (-1);
	}
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	sign;

	i = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	return (calculate_number(str + i, sign));
}
