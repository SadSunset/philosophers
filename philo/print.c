/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:39:39 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:39:42 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdio.h>

void	print_action(t_philo *philo, char *action)
{
	time_t	time;

	time = get_time() - philo->overall_data->start_time;
	printf("%ld %d %s\n", time, philo->number, action);
}
