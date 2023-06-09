/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoubhoum <aoubhoum@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/11 18:57:35 by aoubhoum          #+#    #+#             */
/*   Updated: 2023/06/09 17:59:08 by aoubhoum         ###   ########.fr       */
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
	int				a;
	pthread_mutex_t	last_eat_mutex;
	pthread_mutex_t	print_mutex;
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

int				ft_isdigit(int c);
int				ft_atoi(const char *str);
int				check_arg(int ac, char **av);
void			sleep_re_imple(int time);
int				check_death(t_philo *philo, int ac);
void			init_eat_tims(int nbr_philo, t_philo *philo);
int				init_params(int ac, t_var *var, char **av);
void			handel_dedlock_and_norm(t_philo *philo);
int				ft_strcmp(char *s1, char *s2);
void			my_printf(long long time, char *msg, t_philo *philo);
long long int	get_time(void);

#endif