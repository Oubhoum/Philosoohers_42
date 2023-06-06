/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:06:12 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/06 18:05:33 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long int	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000LL + current_time.tv_usec / 1000LL);
}

void	sleep_re_imple(int time)
{
	long long	var;

	var = get_time();
	while (get_time() - var < time)
		usleep(100);
}

void	check_death(t_philo *philo, int ac)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->var->nb_philo)
		{
			if (get_time() - philo[i].last_eat >= philo[i].var->tm_die)
			{
				printf("%lld %d is died\n", get_time()
					- philo[i].start_time, philo[i].id_philo);
				return ;
			}
			if (ac == 6)
			{
				if (philo[i].counter >= philo[i].var->eat_tims)
				{
					printf("salaw\n");
					return;
				}
			}
			i++;
		}
	}
}

//This function to initalise all eating_tims of eche philosofer by zero
//	to be able to incremet it.

void	init_eat_tims(int nbr_philo, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < nbr_philo)
	{
		philo[i].counter = 0;
		i++;
	}
}

int	check_eat_philo(t_philo *philo, t_var var)
{
	int	i;

	i = 0;
	while (i < var.nb_philo)
	{
		if (philo[i].counter >= var.eat_tims)
			return(printf("salaw\n"), 0);
		i++;
	}
	return(0);
}

int	init_params(int ac, t_var *var, char **av)
{
	if (!check_arg(ac, av))
		return (printf("======= KO :( =======\nParcing Error\n"), 0);
	var->nb_philo = ft_atoi(av[1]);
	var->tm_die = ft_atoi(av[2]);
	var->tm_eat = ft_atoi(av[3]);
	var->tm_sleep = ft_atoi(av[4]);
	if (ac == 6)
		var->eat_tims = ft_atoi(av[5]);
	return (1);
}