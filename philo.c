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

static long long	get_time()
{
	struct timeval currentTime;
	gettimeofday(&currentTime, NULL);
	return (currentTime.tv_sec * 1000LL + currentTime.tv_usec / 1000LL);
}

void	*routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	struct timeval tv;
	while (1)
	{
		pthread_mutex_lock(&philo->mtx_left_fork);
		printf("%d has taken left fork\n", philo->id_philo);
		pthread_mutex_lock(philo->mtx_r_fork);
		printf("%d has taken right fork\n", philo->id_philo);
		printf("%d if eating\n", philo->id_philo);
		gettimeofday(&tv, NULL);
		philo->last_eat = get_time();
		usleep(philo->var.tm_eat);
		pthread_mutex_unlock(&philo->mtx_left_fork);
		printf("%d has put left fork\n", philo->id_philo);
		pthread_mutex_unlock(philo->mtx_r_fork);
		printf("%d has put right fork\n", philo->id_philo);
		printf("%d is sleep\n", philo->id_philo);
		usleep(philo->var.tm_sleep);
		printf("%d is thinking\n", philo->id_philo);
	}
	
	return (NULL);
}


int main(int argc, char **argv)
{
	t_var var;
	t_philo *philo;
	struct timeval tv;
	int current_time;
	var.nb_philo = ft_atoi(argv[1]);
	var.tm_die = ft_atoi(argv[2]);
	var.tm_eat = ft_atoi(argv[3]);
	var.tm_sleep = ft_atoi(argv[4]);

	if (!check_arg(argc, argv))
		printf("======= KO :( =======\n");
	else
		printf("OK :)\n");
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
		long long	current_time_in_seconds = get_time();
		//checki wach khouna waslo lwa9t bach imoot
		// if (philo[i].last_eat * 10000 - current_time * 1000 >= philo->var.tm_die)
		// 	return(0);
		// tdie == last eat - lwa9t diyal drook
		// printf("Time of last eat is: %lld\n", philo->last_eat);
		// printf("Current time is: %lld\n", current_time_in_seconds);
		// sleep(1);
	}
	//moniroting
	// checki last eat m3a  t_die;
	// printi is died;
	// krej
	// pthread_mutex_destroy(&philo[i].mtx_left_fork);
	// pthread_mutex_destroy(philo[i].mtx_r_fork);
	return (0);
}