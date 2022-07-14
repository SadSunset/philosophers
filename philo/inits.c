/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:37:55 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:37:57 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdlib.h>
#include <string.h>

static void	init_overall_numbers(t_overall *all, char **argv)
{
	all->n_philos = ft_atoi(argv[1]);
	all->time_to_die = ft_atoi(argv[2]);
	all->time_to_eat = ft_atoi(argv[3]);
	all->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
		all->n_suppers_goal = ft_atoi(argv[5]);
	else
		all->n_suppers_goal = 0;
}

static void	free_bad_mutex_init(t_overall *all, int created_mutexes)
{
	int	i;

	i = 0;
	while (i < created_mutexes)
	{
		pthread_mutex_destroy(&all->forks[i]);
		i++;
	}
	free(all->philo);
	free(all->forks);
}

static int	init_mutexes(t_overall *all)
{
	int	i;

	i = 0;
	while (i < all->n_philos)
	{
		if (pthread_mutex_init(&all->forks[i], NULL))
		{
			free_bad_mutex_init(all, i);
			return (0);
		}
		i++;
	}
	return (1);
}

static void	init_philos(t_overall *all)
{
	int	i;

	i = 0;
	memset(all->philo, 0, sizeof(t_philo) * all->n_philos);
	while (i < all->n_philos)
	{
		all->philo[i].overall_data = all;
		all->philo[i].number = i + 1;
		all->philo[i].left_fork = &all->forks[i];
		if (i == all->n_philos - 1)
			all->philo[i].right_fork = &all->forks[0];
		else
			all->philo[i].right_fork = &all->forks[i + 1];
		i++;
	}
}

int	init_overall(t_overall *all, char **argv)
{
	memset(all, 0, sizeof(t_overall));
	init_overall_numbers(all, argv);
	all->philo = malloc(sizeof(t_philo) * all->n_philos);
	if (!all->philo)
		return (0);
	all->forks = malloc(sizeof(pthread_mutex_t) * all->n_philos);
	if (!all->forks)
	{
		free(all->philo);
		return (0);
	}
	if (!init_mutexes(all))
		return (0);
	init_philos(all);
	return (1);
}
