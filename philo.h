/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:57:35 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/06 18:04:19 by aoubhoum         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_var
{
	int				nb_philo;
	int				tm_die;
	int				tm_sleep;
	int				tm_eat;
	int				eat_tims;
	pthread_mutex_t	last_eat_mutex;

}	t_var;

typedef struct s_philo
{
	pthread_t		th;
	long long		start_time;
	t_var			*var;
	int				id_philo;
	pthread_mutex_t	mtx_left_fork;
	pthread_mutex_t	*mtx_r_fork;
	long long		last_eat;
	int				counter;
}	t_philo;

int	ft_isdigit(int c);
int	ft_atoi(const char *str);
int	check_arg(int ac, char **av);

//========================= utils2 ================

long long int	get_time(void);
void			sleep_re_imple(int time);
void			check_death(t_philo *philo, int ac);
void			init_eat_tims(int nbr_philo, t_philo *philo);
int				check_eat_philo(t_philo *philo, t_var var);
int				init_params(int ac, t_var *var, char **av);

#endif

