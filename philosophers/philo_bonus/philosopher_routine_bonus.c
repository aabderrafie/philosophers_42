/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:14:06 by aaskal            #+#    #+#             */
/*   Updated: 2024/06/30 14:43:52 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void ft_printf(t_philo *philo, char *str)
{
	long long time;

	time = time_stamp() - philo->data->t;
	sem_wait(philo->data->print_sem);
	printf("%lld %d %s\n", time, philo->id, str);
	sem_post(philo->data->print_sem);
}

void philosopher_actions(t_philo *philo)
{
	ft_printf(philo, "is thinking");
	sem_wait(philo->data->fork);
	ft_printf(philo, "has taken a fork");
	sem_wait(philo->data->fork);
	ft_printf(philo, "has taken a fork");
	sem_wait(philo->data->lmt_sem);
	philo->lmt = time_stamp();
	sem_post(philo->data->lmt_sem);
	ft_printf(philo, "is eating");
	my_sleep(philo->data->tte);
	sem_post(philo->data->fork);
	sem_post(philo->data->fork);
	philo->meals++;
	ft_printf(philo, "is sleeping");
	my_sleep(philo->data->tts);
}

void philosopher_routine(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		ft_printf(philo, "is sleeping");
		my_sleep(philo->data->tts);
	}
	while (1)
	{
		if (philo->meals == philo->data->ntte)
			sem_post(philo->data->meals_sem);
		philosopher_actions(philo);
		if (philo->meals == philo->data->ntte)
			sem_post(philo->data->meals_sem);
		usleep(500);
	}
	exit(0);
}
