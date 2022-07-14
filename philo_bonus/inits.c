/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:40:19 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:41:56 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	init_philo(t_overall *data)
{
	char	*name;

	name = gen_sem_name(data->philo.number);
	data->philo.last_supper = data->start_time;
	data->philo.rights = sem_open(name, O_CREAT | O_EXCL, 0644, data->n_philos);
	if (data->philo.rights == 0)
		write(2, "couldn't open rights semaphore\n", 32);
	sem_unlink(name);
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("stop");
	sem_unlink("repletion");
	free(name);
	if (pthread_create(&data->philo.monitor, NULL, &death_checker, data))
	{
		write(2, "couldnt start thread death_checker", 35);
		sem_post(data->stop);
	}
	pthread_detach(data->philo.monitor);
}

static int	init_sempahore(t_overall *data)
{
	sem_unlink("forks");
	sem_unlink("speak");
	sem_unlink("stop");
	sem_unlink("repletion");
	data->forks = sem_open("forks", O_CREAT | O_EXCL, 0644, data->n_philos);
	data->speak = sem_open("speak", O_CREAT | O_EXCL, 0644, 1);
	data->stop = sem_open("stop", O_CREAT | O_EXCL, 0644, 0);
	if (data->n_suppers_goal)
		data->repletion = sem_open("repletion", O_CREAT | O_EXCL, 0644, 0);
	if (data->forks == 0 || data->speak == 0
		|| data->stop == 0
		|| (data->n_suppers_goal && data->repletion == 0))
	{
		write(2, "couldnt start semaphore", 24);
		return (1);
	}
	return (0);
}

static int	init_thread(t_overall *data)
{
	if (data->n_suppers_goal)
	{
		if (pthread_create(&data->monitor, NULL, &repletion_checker, data))
		{
			write(2, "couldnt start repletion_checker\n", 33);
			return (1);
		}
		pthread_detach(data->monitor);
	}
	return (0);
}

int	init_data(t_overall *data, char **argv)
{
	memset(data, 0, sizeof(t_overall));
	ft_atoi_is_overflow(argv[1], (int *)&data->n_philos);
	ft_atoi_is_overflow(argv[2], (int *)&data->time_to_die);
	ft_atoi_is_overflow(argv[3], (int *)&data->time_to_eat);
	ft_atoi_is_overflow(argv[4], (int *)&data->time_to_sleep);
	if (argv[5])
		ft_atoi_is_overflow(argv[5], (int *)&data->n_suppers_goal);
	data->pid_philo = malloc(sizeof(pid_t) * data->n_philos);
	if (!data->pid_philo)
	{
		write(2, "malloc init_data failed\n", 25);
		return (1);
	}
	memset(data->pid_philo, 0, sizeof(pid_t) * data->n_philos);
	if (init_sempahore(data) == 1
		|| init_thread(data) == 1)
		return (1);
	return (0);
}
