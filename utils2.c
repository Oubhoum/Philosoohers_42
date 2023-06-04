/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 15:06:12 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/04 16:50:40 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return (currentTime.tv_sec * 1000LL + currentTime.tv_usec / 1000LL);
}

void	sleep_re_imple(int time)
{
	long long var;
	
	var = get_time();
	while(get_time() - var < time)
		usleep(100);
}

void	check_death(t_philo *philo)
{
	int	i;
	long long time;

	i = 0;
	// sleep_re_imple(10);
	while (1)
	{
		i = 0;
		time = get_time();
		while(i < philo->var->nb_philo)
		{
			if (time - philo[i].last_eat >= philo[i].var->tm_die)
			{
				printf("%lld %d is died\n", get_time() - philo[i].start_time, philo[i].id_philo);
				return ;
			}
			i++;
		}
	}
}