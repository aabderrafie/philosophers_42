/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:49:36 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/20 10:15:35 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	if_is_dead(t_philo philos)
{
	long	time;

	pthread_mutex_lock(&philos.lm_mutex);
	time = time_stamp() - philos.lmt;
	pthread_mutex_unlock(&philos.lm_mutex);
	if (time > philos.data->ttd)
	{
		pthread_mutex_lock(&philos.data->death_mutexes);
		philos.data->someone_died = 1;
		pthread_mutex_unlock(&philos.data->death_mutexes);
		pthread_mutex_lock(&philos.data->printf_mutex);
		printf("%lld %d died\n", time_stamp() - philos.data->t, philos.id);
		pthread_mutex_unlock(&philos.data->printf_mutex);
		return (1);
	}
	return (0);
}

void	*death_checker(t_philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->data->np)
	{
		pthread_mutex_lock(&philos[i].data->death_mutexes);
		if (!ntte_check(philos + i))
		{
			philos->data->check = 1;
			pthread_mutex_unlock(&philos->data->death_mutexes);
			break ;
		}
		pthread_mutex_unlock(&philos[i].data->death_mutexes);
		if (if_is_dead(philos[i]))
			break ;
		if (i == philos->data->np - 1)
			i = 0;
		else
			i++;
		usleep(500);
	}
	return (NULL);
}
