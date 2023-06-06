/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:05:09 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/06 18:08:51 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	long long		x;

	philo = (t_philo *)arg;
	x = philo->start_time;
	if (philo->id_philo % 2 == 0)
		usleep(100);
	while (1)
	{
		pthread_mutex_lock(&philo->mtx_left_fork);
		printf("%lld %d has taken a fork\n", get_time() - x, philo->id_philo);
		pthread_mutex_lock(philo->mtx_r_fork);
		printf("%lld %d has taken a fork\n", get_time() - x, philo->id_philo);
		printf("%lld %d is eating\n", get_time() - x, philo->id_philo);
		pthread_mutex_lock(&philo->var->last_eat_mutex);
		philo->last_eat = get_time();
		philo->counter++;
		pthread_mutex_unlock(&philo->var->last_eat_mutex);
		sleep_re_imple(philo->var->tm_eat);
		pthread_mutex_unlock(&philo->mtx_left_fork);
		pthread_mutex_unlock(philo->mtx_r_fork);
		printf("%lld %d is sleeping\n", get_time() - x, philo->id_philo);
		sleep_re_imple(philo->var->tm_sleep);
		printf("%lld %d is thinking\n", get_time() - x, philo->id_philo);
	}
	return (NULL);
}

void	ft_creat_thrd(t_philo *philo, t_var *var)
{
	int	i;

	i = 0;
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
}

void	ft_destroy_mutex(t_philo *philo, t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mtx_left_fork);
		pthread_mutex_destroy(philo[i].mtx_r_fork);
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_var			*var;
	t_philo			*philo;
	int				i;

	var = malloc (sizeof(t_var));
	if (!var)
		return (0);
	init_params(argc, var, argv);
	pthread_mutex_init(&var->last_eat_mutex, NULL);
	i = 0;
	philo = malloc(sizeof(t_philo) * var->nb_philo);
	if (!philo)
		return (0);
	init_eat_tims(var->nb_philo, philo);
	ft_creat_thrd(philo, var);
	check_death(philo, argc);
	ft_destroy_mutex(philo, var);
	return (0);
}
