/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 15:11:33 by aaskal            #+#    #+#             */
/*   Updated: 2024/06/10 15:55:26 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	initialize_semaphores(t_data *data)
{
	sem_unlink("/print_sem");
	data->print_sem = sem_open("/print_sem", O_CREAT, 0644, 1);
	sem_unlink("/fork");
	data->fork = sem_open("/fork", O_CREAT, 0644, data->np);
	sem_unlink("/death_sem");
	data->death_sem = sem_open("/death_sem", O_CREAT, 0644, 0);
	sem_unlink("/meals_sem");
	data->meals_sem = sem_open("/meals_sem", O_CREAT, 0644, 1);
	sem_unlink("/lmt_sem");
	data->lmt_sem = sem_open("/lmt_sem", O_CREAT, 0644, 1);
}

int	chek_if_positive(t_data data)
{
	if (data.np <= 0 || data.ttd <= 0 || data.tte <= 0 || data.tts <= 0
		|| data.negative == 1)
	{
		printf("Error: Arguments must be positive\n");
		return (1);
	}
	if (data.np > 200)
	{
		printf("Error: Number of philosophers must be less than 200\n");
		return (1);
	}
	return (0);
}

int	is_number(int argc, char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		if (argv[i][j] == '+' || argv[i][j] == '-')
			j++;
		if (argv[i][j] == '\0')
			return (1);
		while (argv[i][j])
		{
			if ((argv[i][j] < '0' || argv[i][j] > '9') && (argv[i][j] != '\0'))
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	ft_check(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
	{
		printf("Error: Wrong number of arguments\n");
		return (1);
	}
	if (is_number(argc, argv))
	{
		printf("Error: Arguments must be numbers\n");
		return (1);
	}
	return (0);
}

t_data	*init_args(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->np = ft_atoi(argv[1]);
	data->ttd = ft_atoi(argv[2]);
	data->tte = ft_atoi(argv[3]);
	data->tts = ft_atoi(argv[4]);
	data->t = time_stamp();
	initialize_semaphores(data);
	data->negative = 0;
	if (argc == 6)
	{
		data->ntte = ft_atoi(argv[5]);
		if (data->ntte <= 0)
			data->negative = 1;
	}
	else
		data->ntte = -1;
	return (data);
}
