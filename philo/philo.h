/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:39:05 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:39:29 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>

typedef struct s_philo		t_philo;
typedef struct s_overall	t_overall;

# define EAT 0
# define SLEEP 1
# define THINK 2
# define TAKE_FORK 3

typedef struct s_philo
{
	pthread_t		thread;
	int				number;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	time_t			last_supper;
	int				num_supper;
	int				game_over;
	t_overall		*overall_data;
}	t_philo;

typedef struct s_overall
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	voice;
	time_t			start_time;
	int				n_philos;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				n_suppers_goal;
	int				game_over;
}	t_overall;

int		launch_philos(t_overall *all);
int		init_overall(t_overall *all, char **argv);
int		validate_inputs(int argc, char **argv);
time_t	get_time(void);
void	my_sleep(time_t microsec, t_overall *all);
void	print_action(t_philo *philo, char *action);
int		not_int_limits(char *s);
int		ft_atoi(const char *s);
int		ft_strlen(char *s);

#endif
