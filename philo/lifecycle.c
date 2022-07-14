/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:38:06 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:38:09 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <unistd.h>
#include <stdlib.h>

static void	check_death(t_overall *data)
{
	int		i;
	time_t	time;

	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->voice);
		time = get_time();
		while (i < data->n_philos)
		{
			if (time - data->philo[i].last_supper >= data->time_to_die)
			{
				print_action(&data->philo[i], "died");
				data->game_over = 1;
				break ;
			}
			i++;
		}
		if (data->game_over == 1)
		{
			pthread_mutex_unlock(&data->voice);
			return ;
		}
		pthread_mutex_unlock(&data->voice);
	}
}

static int	check_done_eating(t_overall *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (data->philo[i].num_supper < data->n_suppers_goal)
			return (0);
		i++;
	}
	data->game_over = 1;
	return (1);
}

static int	act(t_philo *philo, int action)
{
	pthread_mutex_lock(&philo->overall_data->voice);
	if (philo->overall_data->game_over)
	{
		pthread_mutex_unlock(&philo->overall_data->voice);
		return (1);
	}
	if (action == EAT)
	{
		print_action(philo, "is eating");
		philo->last_supper = get_time();
	}
	else if (action == TAKE_FORK)
		print_action(philo, "has taken a fork");
	else if (action == SLEEP)
	{
		print_action(philo, "is sleeping");
		philo->num_supper++;
		if (philo->num_supper == philo->overall_data->n_suppers_goal)
			check_done_eating(philo->overall_data);
	}
	else if (action == THINK)
		print_action(philo, "is thinking");
	pthread_mutex_unlock(&philo->overall_data->voice);
	return (0);
}

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = arg;
	if (philo->number % 2 == 0)
		my_sleep(philo->overall_data->time_to_eat / 2L, philo->overall_data);
	while (!philo->game_over)
	{
		pthread_mutex_lock(philo->left_fork);
		philo->game_over = act(philo, TAKE_FORK);
		if (philo->left_fork == philo->right_fork)
			break ;
		pthread_mutex_lock(philo->right_fork);
		philo->game_over = act(philo, TAKE_FORK);
		philo->game_over = act(philo, EAT);
		my_sleep(philo->overall_data->time_to_eat, philo->overall_data);
		philo->game_over = act(philo, SLEEP);
		pthread_mutex_unlock(philo->right_fork);
		pthread_mutex_unlock(philo->left_fork);
		my_sleep(philo->overall_data->time_to_sleep, philo->overall_data);
		philo->game_over = act(philo, THINK);
	}
	if (philo->left_fork == philo->right_fork)
		pthread_mutex_unlock(philo->right_fork);
	return (NULL);
}

int	launch_philos(t_overall *all)
{
	int	i;

	i = 0;
	all->start_time = get_time();
	while (i < all->n_philos)
	{
		all->philo[i].last_supper = all->start_time;
		if (pthread_create(&all->philo[i].thread, NULL,
				&routine, &all->philo[i]))
		{
			write(2, "error while pthread_create\n", 28);
			pthread_mutex_lock(&all->voice);
			all->game_over = 1;
			pthread_mutex_unlock(&all->voice);
			return (0);
		}
		i++;
	}
	check_death(all);
	return (1);
}
