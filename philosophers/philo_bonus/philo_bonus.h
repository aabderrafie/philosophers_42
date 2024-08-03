/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaskal <aaskal@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 21:36:07 by aaskal            #+#    #+#             */
/*   Updated: 2024/07/20 10:30:21 by aaskal           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <limits.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>
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
	int					negative;

	sem_t				*print_sem;
	sem_t				*death_sem;
	sem_t				*fork;
	sem_t				*meals_sem;
	sem_t				*lmt_sem;
	pthread_mutex_t		mutex;

}						t_data;

typedef struct s_philo
{
	int					id;
	pid_t				pid;
	long long			lmt;
	pthread_t			thread;
	int					meals;
	t_data				*data;
}						t_philo;

int						ft_check(int argc, char **argv);
t_data					*init_args(int argc, char **argv);
long long				time_stamp(void);
void					my_sleep(long long ms);
void					*death_checker(void *arg);
void					philosopher_routine(t_philo *philo);
void					create_threads(t_philo *philo);
void					ft_printf(t_philo *philo, char *str);
int						ft_atoi(const char *str);
int						chek_if_positive(t_data data);
void					*check_if_eat(void *arg);

#endif