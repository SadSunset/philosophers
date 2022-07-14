/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:40:44 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:41:48 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	arguments_checker(int argc, char **argv)
{
	size_t	i;
	int		tmp;

	if (argc < 5 || argc > 6)
	{
		write(2, "bad input\n", 10);
		return (1);
	}
	i = 1;
	while (argv[i])
	{
		if (!ft_str_isdigit(argv[i]) || ft_atoi_is_overflow(argv[i], &tmp)
			|| tmp == 0)
		{
			write(2, "bad input\n", 10);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	kill_philosophers(t_overall *data)
{
	size_t	i;

	i = 0;
	while (i < data->n_philos)
	{
		kill(data->pid_philo[i], SIGKILL);
		i++;
	}
}

static void	free_data(t_overall *data)
{
	free(data->pid_philo);
	if (sem_close(data->forks))
		write(2, "forks sem_close err\n", 21);
	if (sem_close(data->speak))
		write(2, "speak sem_close err\n", 21);
	if (sem_close(data->stop))
		write(2, "stop sem_close err\n", 20);
	if (data->n_suppers_goal && sem_close(data->repletion))
		write(2, "n_supper_goal sem_close err\n", 29);
}

int	main(int argc, char **argv)
{
	t_overall	data;

	if (arguments_checker(argc, argv) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (init_data(&data, argv) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	if (start_philosopher(&data) == EXIT_FAILURE)
	{
		free_data(&data);
		return (EXIT_FAILURE);
	}
	kill_philosophers(&data);
	free_data(&data);
	return (EXIT_SUCCESS);
}
