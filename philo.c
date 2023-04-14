/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:33:19 by jaizpuru          #+#    #+#             */
/*   Updated: 2023/04/14 15:30:35 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philo *phil, int pos)
{
	pthread_mutex_lock(&(phil->back->philo[pos].fork));
	if (phil->back->shared_fork[pos] == 0)
	{
		phil->back->shared_fork[pos] = 1;
		phil->forks_in_hand += 1;
		print_macro(FORK, phil);
	}
	pthread_mutex_unlock(&phil->back->philo[pos].fork);
}

void	leave_forks(t_philo	*phil, int l_fork, int r_fork)
{
	pthread_mutex_lock(&phil->back->philo[l_fork].fork);
	phil->back->shared_fork[l_fork] = 0;
	pthread_mutex_unlock(&phil->back->philo[l_fork].fork);
	pthread_mutex_lock(&phil->back->philo[r_fork].fork);
	phil->back->shared_fork[r_fork] = 0;
	pthread_mutex_unlock(&phil->back->philo[r_fork].fork);
	phil->forks_in_hand = 0;
}

void	*ft_kitchen(t_philo	*phil)
{
	int		left_fork;
	int		right_fork;

	left_fork = phil->id - 1;
	right_fork = phil->id % phil->back->n_philo;
	if (phil->id % 2 == 0)
	{
		left_fork = phil->id % phil->back->n_philo;
		right_fork = phil->id - 1;
	}
	while (phil->forks_in_hand < 2 && !is_dead(phil))
	{
		take_fork(phil, left_fork);
		take_fork(phil, right_fork);
	}
	if (!is_dead(phil))
	{
		print_macro(EAT, phil);
		phil->n_eats++;
		phil->t_death = ft_diff(phil->back->time) + phil->back->t_die;
		ft_atomic((long)phil->back->t_eat, phil->back->n_philo, phil);
		leave_forks(phil, left_fork, right_fork);
	}
	return (NULL);
}

void	philo_routine(t_philo	*phil)
{
	while (!is_dead(phil))
	{
		if (ft_kitchen(phil) != NULL)
			return ;
		if (phil->n_eats == phil->back->n_times_eat)
			return ;
		print_macro(SLEEP, phil);
		ft_atomic((long)phil->back->t_sleep, phil->back->n_philo, phil);
		print_macro(THINK, phil);
	}
}

void	*thread_routine(void *data)
{
	t_philo	*phil;

	phil = (t_philo *)data;

	phil->t_death = ft_diff(phil->back->time) + phil->back->t_die;
	if (phil->id % 2 && phil->back->n_philo != 1)
		ft_atomic(phil->back->t_eat / 2, phil->back->n_philo, phil);
	philo_routine(phil);
	return (NULL);
}
