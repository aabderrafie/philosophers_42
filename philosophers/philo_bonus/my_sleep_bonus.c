/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:44:30 by aaskal            #+#    #+#             */
/*   Updated: 2024/06/22 17:20:06 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

long long	time_stamp(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_sleep(long long ms)
{
	long long	start;
	long long	elapsed;

	start = time_stamp();
	while (1)
	{
		elapsed = time_stamp() - start;
		if (elapsed >= ms)
			break ;
		usleep(500);
	}
}
