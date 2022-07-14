/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:40:55 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:41:46 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>
# include <pthread.h>
# include <fcntl.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_philo		t_philo;
typedef struct s_overall	t_overall;

# define EAT 0
# define SLEEP 1
# define THINK 2
# define TAKE_FORK 3

typedef struct s_philo
{
	pthread_t	monitor;
	sem_t		*rights;
	size_t		number;
	time_t		last_supper;
	size_t		num_supper;
	size_t		n_suppers_goal;
}	t_philo;

typedef struct s_overall
{
	pthread_t	monitor;
	pid_t		*pid_philo;
	t_philo		philo;
	sem_t		*forks;
	sem_t		*speak;
	sem_t		*stop;
	sem_t		*repletion;
	time_t		start_time;
	size_t		n_philos;
	time_t		time_to_die;
	time_t		time_to_eat;
	time_t		time_to_sleep;
	size_t		n_suppers_goal;
}	t_overall;

int		init_data(t_overall *data, char **argv);
void	init_philo(t_overall *data);
int		start_philosopher(t_overall *data);
void	*death_checker(void *arg);
void	*repletion_checker(void *arg);
void	ft_putstr_fd(const char *s, int fd);
int		ft_str_isdigit(char *str);
size_t	ft_strlen(const char *str);
int		ft_atoi_is_overflow(const char *str, int *nb);
time_t	get_time(void);
void	print_action(t_overall *data, t_philo *philo, char *action);
void	my_sleep(time_t microseconds, t_overall *data);
char	*gen_sem_name(int philo_id);

#endif
