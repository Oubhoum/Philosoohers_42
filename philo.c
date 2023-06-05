/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:05:09 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/05 19:52:33 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	int				y;

	y = philo->id_philo;
	philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx_left_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->start_time, y);
		pthread_mutex_lock(philo->mtx_r_fork);
		printf("%lld %d has taken a fork\n", get_time() - philo->start_time, y);
		printf("%lld %d is eating\n", get_time() - philo->start_time, y);
		pthread_mutex_lock(&philo->var->last_eat_mutex);
		philo->last_eat = get_time();
		pthread_mutex_unlock(&philo->var->last_eat_mutex);
		sleep_re_imple(philo->var->tm_eat);
		pthread_mutex_unlock(&philo->mtx_left_fork);
		pthread_mutex_unlock(philo->mtx_r_fork);
		printf("%lld %d is sleeping\n", get_time() - philo->start_time, y);
		sleep_re_imple(philo->var->tm_sleep);
		printf("%lld %d is thinking\n", get_time() - philo->start_time, y);
	}
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_var			*var;
	t_philo			*philo;
	int				i;

	if (!check_arg(argc, argv))
		return (printf("======= KO :( =======\nParcing Error\n"), 0);
	var = malloc (sizeof(t_var));
	if (!var)
		return (0);
	var->nb_philo = ft_atoi(argv[1]);
	var->tm_die = ft_atoi(argv[2]);
	var->tm_eat = ft_atoi(argv[3]);
	var->tm_sleep = ft_atoi(argv[4]);
	pthread_mutex_init(&var->last_eat_mutex, NULL);
	i = 0;
	philo = malloc(sizeof(t_philo) * var->nb_philo);
	if (!philo)
		return (0);
	while (i < var->nb_philo)
	{
		philo[i].id_philo = i + 1;
		philo[i].var = var;
		pthread_mutex_init(&philo[i].mtx_left_fork, NULL);
		if (i + 1 == var->nb_philo)
			philo[i].mtx_r_fork = &philo[0].mtx_left_fork;
		else
			philo[i].mtx_r_fork = &philo[i + 1].mtx_left_fork;
		philo[i].last_eat = get_time();
		philo[i].start_time = get_time();
		pthread_create(&philo[i].th, NULL, &routine, &philo[i]);
		pthread_detach(philo[i].th);
		i++;
	}
	check_death(philo);
	i = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mtx_left_fork);
		pthread_mutex_destroy(philo[i].mtx_r_fork);
		i++;
	}
	return (0);
}
