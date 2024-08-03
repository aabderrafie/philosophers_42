/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:14:20 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/19 09:28:58 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void destroy(t_philo *philo)
{
	int i;
	t_philo *tmp;

	i = 0;
	tmp = philo;
	while (i < tmp->data->np)
	{
		pthread_mutex_destroy(tmp[i].lf);
		pthread_mutex_destroy(&tmp[i].meals_mutex);
		pthread_mutex_destroy(&tmp[i].lm_mutex);
		free(tmp[i].lf);
		i++;
	}
	free(tmp->data);
	free(tmp);
}

void init_philosopher(t_philo *philo, t_data *data)
{
	int i;
	long long t;

	i = 0;
	t = time_stamp();
	while (i < data->np)
	{
		philo[i].id = i + 1;
		philo[i].data = data;
		philo[i].lmt = t;
		philo[i].meals = 0;
		philo[i].lf = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(philo[i].lf, NULL);
		pthread_mutex_init(&philo[i].meals_mutex, NULL);
		pthread_mutex_init(&philo[i].lm_mutex, NULL);
		if (i != 0)
			philo[i].rf = philo[i - 1].lf;
		i++;
	}
	philo[0].rf = philo[data->np - 1].lf;
}

int ntte_check(t_philo *philo)
{
	int i;
	int meals;

	i = 0;
	if (philo->data->ntte == -1)
		return (1);
	while (i < philo->data->np)
	{
		pthread_mutex_lock(&philo[i].meals_mutex);
		meals = philo[i].meals;
		pthread_mutex_unlock(&philo[i].meals_mutex);
		if (meals < philo->data->ntte)
			return (1);
		i++;
	}
	return (0);
}

void *create_threads(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->np)
	{
		pthread_create(&philo[i].thread, NULL, philosopher_routine, &philo[i]);
		i++;
	}
	if (philo->data->np != 1)
		death_checker(philo);
	i = 0;
	while (i < philo->data->np)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_data *data;

	if (ft_check(argc, argv))
		return (1);
	data = init_args(argc, argv);
	if (chek_if_positive(*data))
	{
		free(data);
		return (1);
	}
	philo = malloc(sizeof(t_philo) * data->np);
	pthread_mutex_init(&data->printf_mutex, NULL);
	pthread_mutex_init(&data->death_mutexes, NULL);
	init_philosopher(philo, data);
	create_threads(philo);
	destroy(philo);
	return (0);
}
