/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:06:12 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/08 13:43:54 by aoubhoum         ###   ########.fr       */
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

int	check_death(t_philo *philo, int ac)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < philo->var->nb_philo)
		{
			pthread_mutex_lock(&philo[i].var->last_eat_mutex);
			if (get_time() - philo[i].last_eat >= philo[i].var->tm_die)
			{
				printf("%lld %d is died\n", get_time()
					- philo[i].start_time, philo[i].id_philo);
				return (0);
			}
			if (ac == 6)
				if (philo[i].counter > philo[i].var->eat_tims)
					return (0);
			pthread_mutex_unlock(&philo[i].var->last_eat_mutex);
			i++;
		}
	}
	return (1);
}

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
