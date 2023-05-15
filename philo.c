/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 19:05:09 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/05/15 14:35:42 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


// void	*routine(void *arg)
// {
// 	t_var	*var = (t_var)arg;

// 	pthread_mutex_lock(&var.mutex);
// 	int philosophers = var->id_philo;
// 	int i = 0;
// 	while (i  < philosophers)
// 	{
// 		printf("Routine %d\n", i + 1);
// 		i++;
// 		sleep(1);
// 	}
// 	printf("=====================\n");
// 	pthread_mutex_unlock(&var.mutex);
// }

void	*routine(void *arg)
{
	// t_var *var = (t_var *)arg;
	t_philo pl;
	
	while (1)
	{
		// boucle infinie
		// locki left;
		pthread_mutex_lock(&pl.mtx_left_fork);
		printf("Philo number %d has taken left fork\n", pl.var.nb_philo);
		// printi : has taken a fork;
		// locki right;
		pthread_mutex_lock(pl.mtx_r_fork);
		printf("Philo number %d has taken right fork\n", pl.var.nb_philo);
		// printi : has taken a fork;
		// printi is eating;
		printf("The philosopher if eating");
		// last_eat = lo9t fach bda lmakla;
		// usleep(t_eat);
		usleep(pl.var.tm_eat);
		// unlock right;
		pthread_mutex_unlock(&pl.mtx_left_fork);
		//	unock left; 
		pthread_mutex_unlock(pl.mtx_r_fork);
		// printi  id sleeping
		printf("Philo number %d is sleep\n", pl.var.nb_philo);
		// usleep(t_sleep);
		usleep(pl.var.tm_sleep);
		// printi is thinking
		printf("The philosopher number %d is thinking\n", pl.var.nb_philo);
	}
	
	return (NULL);
}


int main(int argc, char **argv)
{
	t_var var;
	t_philo philo;
	// t_philo *philo;
	var.nb_philo = ft_atoi(argv[1]);
	var.tm_die = ft_atoi(argv[2]);
	var.tm_eat = ft_atoi(argv[3]);
	var.tm_sleep = ft_atoi(argv[4]);

	// philo = malloc(sizeof(t_philo) * var.nb_philo);
	printf("=====================\n");
	if (!check_arg(argc, argv))
		printf("======= KO :( =======\n");
	else
		printf("OK :)\n");
	printf("=====================\n");
	philo.th[var.nb_philo];
	int i = 0;
	pthread_mutex_init(&philo.mtx_left_fork, NULL);
	pthread_mutex_init(philo.mtx_r_fork, NULL);
	while (i < var.nb_philo)
    {

		// printf("philo number %d\n", i + 1);
		pthread_create(&philo.th[i], NULL, &routine, &var);
		pthread_join(philo.th[i], NULL);
		i++;
	}
	//moniroting
	// checki last eat m3a  t_die;
	// printi is died;
	// krej
	pthread_mutex_destroy(&philo.mtx_left_fork);
	pthread_mutex_destroy(philo.mtx_r_fork);
	return (0);
}