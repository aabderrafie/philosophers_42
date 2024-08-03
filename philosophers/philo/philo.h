/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:36:07 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/01 10:40:12 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct timeval	t_timeval;

typedef struct s_data
{
	int					np;
	long long			t;
	int					ttd;
	int					tte;
	int					tts;
	int					ntte;
	int					someone_died;
	int					negative;

	pthread_mutex_t		death_mutexes;
	pthread_mutex_t		printf_mutex;

	int					check;
}						t_data;

typedef struct s_philo
{
	int					id;
	pthread_t			thread;
	pthread_mutex_t		*lf;
	pthread_mutex_t		*rf;
	pthread_mutex_t		meals_mutex;
	pthread_mutex_t		lm_mutex;
	long long			lmt;
	int					meals;

	t_data				*data;
}						t_philo;

int						ft_check(int argc, char **argv);
t_data					*init_args(int argc, char **argv);
long long				time_stamp(void);
void					my_sleep(long long ms, t_philo *philo);
void					*death_checker(t_philo	*philos);
void					*philosopher_routine(void *arg);
void					*create_threads(t_philo *philo);
void					*ft_printf(t_philo *philo, char *str);
int						ntte_check(t_philo *philo);
void					lonely(t_philo *philo);
int						ft_atoi(const char *str);
int						chek_if_positive(t_data data);
void					destroy(t_philo *philo);

#endif