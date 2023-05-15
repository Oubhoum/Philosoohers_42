/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:06:13 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/05/12 11:52:26 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static	int	check_plus_singe_position(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			if (str[i] && !ft_isdigit(str[i]))
				return (0);
			i -= 2;
			if (i >= 0 && ft_isdigit(str[i]))
				return (0);
			i++;
		}
		i++;
	}
	return (1);
}

int	check_arg(int ac, char **av)
{
	int	i;
	int	j;

	if (ac != 5)
		return (0);
	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (!ft_isdigit(av[i][j]) && av[i][j] != '+')
				return (0);
			j++;
		}
		i++;
	}
	i = 0;
	while (av[i])
	{
		if (!check_plus_singe_position(av[i]))
			return (0);
		i++;
	}
	return (1);
}
