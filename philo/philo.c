/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:05:09 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/09 17:56:18 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*routine(void *arg)
{
	t_philo			*philo;
	long long		x;

	philo = (t_philo *)arg;
	x = philo->start_time;
	handel_dedlock_and_norm(philo);
	while (philo->var->a == 1)
	{
		pthread_mutex_lock(&philo->mtx_left_fork);
		my_printf(x, "has taken a fork\n", philo);
		pthread_mutex_lock(philo->mtx_r_fork);
		my_printf(x, "has taken a fork\n", philo);
		my_printf(x, "is eating\n", philo);
		pthread_mutex_lock(&philo->var->last_eat_mutex);
		philo->last_eat = get_time();
		philo->counter++;
		pthread_mutex_unlock(&philo->var->last_eat_mutex);
		sleep_re_imple(philo->var->tm_eat);
		pthread_mutex_unlock(&philo->mtx_left_fork);
		pthread_mutex_unlock(philo->mtx_r_fork);
		my_printf(x, "is sleeping\n", philo);
		sleep_re_imple(philo->var->tm_sleep);
		my_printf(x, "is thinking\n", philo);
	}
	return (NULL);
}

static void	ft_creat_thrd(t_philo *philo, t_var *var)
{
	int	i;

	i = 0;
	var->a = 1;
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

static void	ft_destroy_mutex(t_philo *philo, t_var *var)
{
	int	i;

	i = 0;
	while (i < var->nb_philo)
	{
		pthread_mutex_destroy(&philo[i].mtx_left_fork);
		pthread_mutex_destroy(philo[i].mtx_r_fork);
		i++;
	}
	pthread_mutex_destroy(&philo->var->last_eat_mutex);
	pthread_mutex_destroy(&philo->var->print_mutex);
}

int	main(int argc, char **argv)
{
	t_var			*var;
	t_philo			*philo;

	var = malloc (sizeof(t_var));
	if (!var)
		return (0);
	if (!init_params(argc, var, argv))
		return (0);
	pthread_mutex_init(&var->last_eat_mutex, NULL);
	pthread_mutex_init(&var->print_mutex, NULL);
	philo = malloc(sizeof(t_philo) * var->nb_philo);
	if (!philo)
		return (0);
	init_eat_tims(var->nb_philo, philo);
	ft_creat_thrd(philo, var);
	if (!check_death(philo, argc))
		return (ft_destroy_mutex(philo, var), 0);
	ft_destroy_mutex(philo, var);
	return (0);
}
