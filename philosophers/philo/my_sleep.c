/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_sleep.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:44:30 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/01 10:51:37 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	time_stamp(void)
{
	t_timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	my_sleep(long long ms, t_philo *philo)
{
	long long	start;
	long long	elapsed;
	int			death;
	int			check;

	start = time_stamp();
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutexes);
		death = philo->data->someone_died;
		pthread_mutex_unlock(&philo->data->death_mutexes);
		pthread_mutex_lock(&philo->data->death_mutexes);
		check = philo->data->check;
		pthread_mutex_unlock(&philo->data->death_mutexes);
		elapsed = time_stamp() - start;
		if (elapsed >= ms || death || check)
			break ;
		usleep(999);
	}
}
