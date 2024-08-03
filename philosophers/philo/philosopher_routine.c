/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_routine.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 23:14:06 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/20 10:14:28 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lonely(t_philo *philo)
{
	ft_printf(philo, "is thinking");
	pthread_mutex_lock(philo->lf);
	ft_printf(philo, "has taken a fork");
	my_sleep(philo->data->ttd, philo);
	ft_printf(philo, "died");
	pthread_mutex_unlock(philo->lf);
}

void	*ft_printf(t_philo *philo, char *str)
{
	int	check;

	pthread_mutex_lock(&philo->data->printf_mutex);
	pthread_mutex_lock(&philo->data->death_mutexes);
	check = philo->data->someone_died;
	pthread_mutex_unlock(&philo->data->death_mutexes);
	if (!check)
		printf("%lld %d %s\n", time_stamp() - philo->data->t, philo->id, str);
	pthread_mutex_unlock(&philo->data->printf_mutex);
	return (NULL);
}

void	*philosopher_actions(t_philo *philo)
{
	ft_printf(philo, "is thinking");
	pthread_mutex_lock(philo->lf);
	ft_printf(philo, "has taken a fork");
	pthread_mutex_lock(philo->rf);
	ft_printf(philo, "has taken a fork");
	ft_printf(philo, "is eating");
	pthread_mutex_lock(&philo->lm_mutex);
	philo->lmt = time_stamp();
	pthread_mutex_unlock(&philo->lm_mutex);
	my_sleep(philo->data->tte, philo);
	pthread_mutex_unlock(philo->rf);
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_lock(&philo->meals_mutex);
	philo->meals++;
	pthread_mutex_unlock(&philo->meals_mutex);
	ft_printf(philo, "is sleeping");
	my_sleep(philo->data->tts, philo);
	return (NULL);
}

void	*philosopher_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->np == 1)
		return (lonely(philo), NULL);
	if (philo->id % 2 == 0)
	{
		ft_printf(philo, "is sleeping");
		my_sleep(philo->data->tts, philo);
	}
	while (1)
	{
		pthread_mutex_lock(&philo->data->death_mutexes);
		if (philo->data->someone_died || philo->data->check)
		{
			pthread_mutex_unlock(&philo->data->death_mutexes);
			break ;
		}
		pthread_mutex_unlock(&philo->data->death_mutexes);
		philosopher_actions(philo);
		usleep(500);
	}
	return (NULL);
}
