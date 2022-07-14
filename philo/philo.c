/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:38:45 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:38:47 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include "philo.h"

static void	free_all(t_overall *data)
{
	int	i;

	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_join(data->philo[i].thread, NULL))
			write(2, "thread join fail\n", 18);
		i++;
	}
	free(data->philo);
	i = 0;
	while (i < data->n_philos)
	{
		if (pthread_mutex_destroy(&data->forks[i]))
			write(2, "forks mutex destroy fail\n", 26);
		i++;
	}
	free(data->forks);
	if (pthread_mutex_destroy(&data->voice))
		write(2, "voice mutex destroy fail\n", 26);
}

int	main(int argc, char **argv)
{
	t_overall	all;

	if (!validate_inputs(argc, argv))
	{
		write(2, "bad input\n", 11);
		return (1);
	}
	if (!init_overall(&all, argv))
	{
		write(2, "init failure\n", 14);
		return (1);
	}
	if (!launch_philos(&all))
	{
		write(2, "couldn't start threads\n", 24);
		return (1);
	}
	free_all(&all);
}
