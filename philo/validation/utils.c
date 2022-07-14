/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbinary <fbinary@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/28 17:37:28 by fbinary           #+#    #+#             */
/*   Updated: 2022/06/28 17:37:31 by fbinary          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

int	ft_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

static int	is_space(const char c)
{
	if (c == '\v' || c == '\t' || c == '\n'
		|| c == ' ' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

static void	init(int *a, long *b, long *c)
{
	*a = 0;
	*b = 1;
	*c = 0;
}

int	ft_atoi(const char *s)
{
	int		str_index;
	long	sign;
	long	result;

	init(&str_index, &sign, &result);
	while (is_space(s[str_index]))
		str_index++;
	if (s[str_index] == '-')
	{
		str_index++;
		sign = -1;
	}
	else if (s[str_index] == '+')
		str_index++;
	while (s[str_index] >= '0' && s[str_index] <= '9')
	{
		result = (result * 10) + (s[str_index] - '0');
		str_index++;
	}
	return ((int)result * sign);
}

int	not_int_limits(char *s)
{
	int		str_index;
	long	sign;
	long	result;

	init(&str_index, &sign, &result);
	while (is_space(s[str_index]))
		str_index++;
	if (s[str_index] == '-')
	{
		str_index++;
		sign = -1;
	}
	else if (s[str_index] == '+')
		str_index++;
	while (s[str_index] >= '0' && s[str_index] <= '9')
	{
		result = (result * 10) + (s[str_index] - '0');
		if (sign == -1 && result > 2147483648)
			return (1);
		if (sign == 1 && result > 2147483647)
			return (1);
		str_index++;
	}
	return (0);
}
