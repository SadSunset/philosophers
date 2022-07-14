/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:41:02 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:41:42 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

time_t	get_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_sec * 1000L + time.tv_usec / 1000L);
}

void	print_action(t_overall *data, t_philo *philo, char *action)
{
	time_t	time;

	time = get_time() - data->start_time;
	printf("%ld %ld %s\n", time, philo->number, action);
}

void	my_sleep(time_t microseconds, t_overall *data)
{
	time_t	start;

	start = get_time();
	while (get_time() - start < microseconds)
	{
		if (data->n_philos < 100)
			usleep(100);
		else
			usleep(1000);
	}
}

char	*gen_sem_name(int philo_id)
{
	int		index;
	int		tmp;
	char	*name;

	index = 2;
	tmp = philo_id;
	while (tmp > 9)
	{
		tmp /= 10;
		index++;
	}
	name = malloc(index * sizeof(char));
	name[0] = 'p';
	name[index--] = '\0';
	while (philo_id > 9)
	{
		name[index] = philo_id % 10 + '0';
		philo_id /= 10;
		index--;
	}
	name[index] = philo_id % 10 + '0';
	return (name);
}
