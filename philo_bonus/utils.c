/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:41:31 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:41:40 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_putstr_fd(const char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

int	ft_str_isdigit(char *str)
{
	while (*str)
	{
		if (!('0' <= *str && *str <= '9'))
			return (0);
		str++;
	}
	return (1);
}

size_t	ft_strlen(const char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_atoi_is_overflow(const char *str, int *nb)
{
	int		sign;

	*nb = 0;
	sign = 1;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while ('0' <= *str && *str <= '9')
	{
		*nb = *nb * 10 + (*str - 48) * sign;
		if ((sign == -1 && *nb > 0) || (sign == 1 && *nb < 0))
			return (1);
		str++;
	}
	return (0);
}
