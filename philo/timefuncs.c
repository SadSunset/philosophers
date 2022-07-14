/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   timefuncs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:39:47 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:39:51 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <unistd.h>
#include "philo.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	my_sleep(time_t microsec, t_overall *all)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < microsec)
	{
		pthread_mutex_lock(&all->voice);
		if (all->game_over)
		{
			pthread_mutex_unlock(&all->voice);
			break ;
		}
		pthread_mutex_unlock(&all->voice);
		if (all->n_philos < 100)
			usleep(10);
		else
			usleep(50);
	}
}
