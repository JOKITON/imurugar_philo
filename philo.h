/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:19:33 by hedgedog          #+#    #+#             */
/*   Updated: 2023/04/12 14:00:20 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>

# define TRUE 1
# define FALSE 0
# define FORK 1
# define EAT 2
# define SLEEP 3
# define THINK 4
# define DIE 5

typedef struct s_philo
{
	int				id;
	int				n_eats;
	long			t_death;
	int				forks_in_hand;
	pthread_t		thread;
	pthread_mutex_t	fork;
	struct s_data	*back;
}		t_philo;

typedef struct s_data
{
	int				n_philo;
	int				forks;
	char			*shared_fork;
	pthread_mutex_t	death;
	time_t			t_die;
	time_t			t_eat;
	time_t			t_sleep;
	int				n_times_eat;
	long			time;
	struct timeval	start;
	volatile bool	check;
	pthread_mutex_t	print;
	t_philo			*philo;
}			t_data;

void	*thread_routine(void	*data);
int		ft_atoi(const char *str);
int		get_philo(t_data	*data);
int		ft_msleep(long milisecons, int num_philos);
void	init_philos(t_data	*data);

int		ft_atomic(long ms, int philos, t_philo	*phil);
long	ft_diff(long before);
int		is_dead(t_philo	*philo);
int		check_any_die(t_philo	*philo);
void	print_macro(int macro, t_philo	*philo);
void	clear_all(t_data *data);
void	wait_for_eats(t_philo	*phil, pthread_mutex_t	*p_right_fork);

#endif