/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_checker_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 11:49:36 by aaskal            #+#    #+#             */
/*   Updated: 2024/06/22 16:21:18 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void *death_checker(void *arg)
{
	t_philo *philos;
	long time;
	long long timer;

	philos = (t_philo *)arg;
	while (1)
	{
		sem_wait(philos->data->lmt_sem);
		time = time_stamp() - philos->lmt;
		timer = time_stamp() - philos->data->t;
		sem_post(philos->data->lmt_sem);
		if (time > philos->data->ttd)
		{
			sem_wait(philos->data->print_sem);
			printf("%lld %d died\n", timer, philos->id);
			sem_post(philos->data->death_sem);
		}
		usleep(500);
	}
	exit(0);
}
