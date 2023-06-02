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
	t_philo *philo = (t_philo *)arg;
	
	while (1)
	{
		// boucle infinie
		// locki left;
		pthread_mutex_lock(&philo->mtx_left_fork);
		printf("%d has taken left fork\n", philo->id_philo);
		// printi : has taken a fork;
		// locki right;
		pthread_mutex_lock(philo->mtx_r_fork);
		printf("%d has taken right fork\n", philo->id_philo);
		// printi : has taken a fork;
		// printi is eating;
		printf("%d if eating\n", philo->id_philo);
		// last_eat = lo9t fach bda lmakla;
		// usleep(t_eat);
		usleep(philo->var.tm_eat);
		// unlock right;
		pthread_mutex_unlock(&philo->mtx_left_fork);
		//	unock left; 
		pthread_mutex_unlock(philo->mtx_r_fork);
		// printi  id sleeping
		printf("%d is sleep\n", philo->id_philo);
		// usleep(t_sleep);
		// usleep(philo->var.tm_sleep);
		sleep(1);
		// printi is thinking
		printf("%d is thinking\n", philo->id_philo);
	}
	
	return (NULL);
}


int main(int argc, char **argv)
{
	t_var var;
	t_philo *philo;
	// t_philo *philo;
	var.nb_philo = ft_atoi(argv[1]);
	var.tm_die = ft_atoi(argv[2]);
	var.tm_eat = ft_atoi(argv[3]);
	var.tm_sleep = ft_atoi(argv[4]);

	// philo = malloc(sizeof(t_philo) * var.nb_philo);
	// printf("=====================\n");
	if (!check_arg(argc, argv))
		printf("======= KO :( =======\n");
	else
		printf("OK :)\n");
	// printf("=====================\n");
	// philo.th = malloc(sizeof(t_philo) * var.nb_philo);
	// if (!philo.th)
		// return(0);
	// pthread_mutex_init(&philo.mtx_left_fork, NULL);
	// pthread_mutex_init(&philo.mtx_r_fork, NULL);
	int i = 0;

	philo = malloc(sizeof(t_philo) * var.nb_philo);
	if (!philo)
		return (0);

	while (i < var.nb_philo)
    {
		philo[i].id_philo = i + 1;
		printf("philo number %d\n", philo[i].id_philo);

		philo[i].var = var;
		pthread_mutex_init(&philo[i].mtx_left_fork, NULL);
		if (i + 1 == var.nb_philo)
			philo[i].mtx_r_fork = &philo[0].mtx_left_fork;	
		else
			philo[i].mtx_r_fork = &philo[i + 1].mtx_left_fork;
		philo[i].last_eat = 0;
		pthread_create(&philo[i].th, NULL, &routine, &philo[i]);
		// pthread_detach(philo[i].th);
		i++;
	}
	while (1)
	{
		//checki wach khouna waslo lwa9t bach imoot
		// tdie == last eat - lwa9t diyal drook
	};
	//moniroting
	// checki last eat m3a  t_die;
	// printi is died;
	// krej
	// pthread_mutex_destroy(&philo[i].mtx_left_fork);
	// pthread_mutex_destroy(&philo[i].mtx_r_fork);
	return (0);
}