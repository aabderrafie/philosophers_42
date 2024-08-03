/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:14:20 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/20 10:36:16 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void kill_all(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->data->np)
	{
		kill(philo[i].pid, SIGKILL);
		i++;
	}
}

void *check_if_eat(void *arg)
{
	t_philo *philo;
	int i;

	philo = (t_philo *)arg;
	i = 0;
	while (i < philo->data->np)
	{
		sem_wait(philo[i].data->meals_sem);
		i++;
	}
	sem_post(philo->data->death_sem);
	return (NULL);
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
		i++;
	}
}

void create_philosophers(t_philo *philo)
{
	int i;
	pthread_t thread;

	i = 0;
	sem_unlink("/meals_sem");
	philo->data->meals_sem = sem_open("/meals_sem", O_CREAT, 0644, 0);
	while (i < philo->data->np)
	{
		philo[i].pid = fork();
		if (philo[i].pid == 0)
		{
			pthread_create(&philo[i].thread, NULL, death_checker, &philo[i]);
			philosopher_routine(&philo[i]);
		}
		i++;
	}
	pthread_create(&thread, NULL, check_if_eat, philo);
	sem_wait(philo->data->death_sem);
	kill_all(philo);
}

int main(int argc, char **argv)
{
	t_philo *philo;
	t_data *data;

	if (ft_check(argc, argv))
		exit(1);
	data = init_args(argc, argv);
	if (chek_if_positive(*data))
	{
		free(data);
		exit(1);
	}
	philo = malloc(sizeof(t_philo) * data->np);
	if (!philo)
		exit(1);
	init_philosopher(philo, data);
	create_philosophers(philo);
	free(philo);
	free(data);
	return (0);
}
