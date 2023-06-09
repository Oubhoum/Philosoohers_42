/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:17:55 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/09 18:00:06 by aoubhoum         ###   ########.fr       */
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
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		singe = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * singe);
}

int	init_params(int ac, t_var *var, char **av)
{
	if (!check_arg(ac, av))
		return (printf("======= KO :( =======\nParcing Error\n"), 0);
	var->nb_philo = ft_atoi(av[1]);
	if (var->nb_philo == 0)
		return (printf("Error: invalid arguments\n"), 0);
	var->tm_die = ft_atoi(av[2]);
	var->tm_eat = ft_atoi(av[3]);
	var->tm_sleep = ft_atoi(av[4]);
	if (ac == 6)
	{
		var->eat_tims = ft_atoi(av[5]);
		if (var->eat_tims <= 0)
			return (printf("Error: invalid arguments\n"), 0);
	}
	return (1);
}

void	handel_dedlock_and_norm(t_philo *philo)
{
	if (philo->id_philo % 2 == 0)
		sleep_re_imple(200);
}

void	my_printf(long long time, char *msg, t_philo *philo)
{
	pthread_mutex_lock(&philo->var->print_mutex);
	printf("%lld %d %s", get_time() - time, philo->id_philo, msg);
	if (ft_strcmp(msg, "is died\n") != 0)
		pthread_mutex_unlock(&philo->var->print_mutex);
}
