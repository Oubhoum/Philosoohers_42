/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:57:35 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/05/15 14:12:35 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>

typedef struct s_var
{
	int	nb_philo;
	int	tm_die;
	int	tm_sleep;
	int tm_eat;

}   t_var;

typedef struct s_philo
{
	pthread_t       th;
	t_var			var;
	int				id_philo;
	pthread_mutex_t	mtx_left_fork;
	pthread_mutex_t	*mtx_r_fork;
	int				last_eat;
	//struct s_philo *next;
}	t_philo;


int	ft_isdigit(int c);
int	ft_atoi(const char *str);
int	check_arg(int ac, char **av);

#endif