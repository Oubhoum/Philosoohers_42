/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:17:55 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/05/12 19:30:13 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int	ft_atoi(const char *str)
{
	int					i;
	unsigned long long	result;
	int					singe;

	i = 0;
	result = 0;
	singe = 1;
	while (str[i] == ' ' || (str[i] >= '\t' && str[i] <= '\r'))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			singe *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
		if (result > 2147483647 && singe == 1)
			return (write(2, "Error\n", 6), exit(1), 0);
		if (result > 2147483648 && singe == -1)
			return (write(2, "Error\n", 6), exit(1), 0);
	}
	return (result * singe);
}
