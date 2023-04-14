/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 13:33:19 by jaizpuru          #+#    #+#             */
/*   Updated: 2023/04/13 16:20:10 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutexes(t_philo	*philo)
{
	pthread_mutex_destroy(&philo->sleep);
	pthread_mutex_destroy(&philo->fork);
	pthread_mutex_destroy(&philo->death);
}

int	is_dead(t_philo	*philo)
{
	pthread_mutex_lock(&philo->death);
	if (!philo->t_death || !philo->back->time)
		return (0);
	if (ft_diff(philo->back->time) >= (philo->t_death)
		&& !philo->back->check)
	{
		pthread_mutex_lock(&philo->back->print);
		philo->back->check = TRUE;
		printf("%ldms %d died\n", ft_diff(philo->back->time), philo->id);
		pthread_mutex_unlock(&philo->back->print);
		pthread_mutex_unlock(&philo->death);
		pthread_mutex_destroy(&philo->back->print);
		return (1);
	}
	pthread_mutex_unlock(&philo->death);
	return (0);
}

void	*ft_kitchen(t_philo	*phil)
{
	pthread_mutex_t	*right_fork;

	if (phil->id == phil->back->n_philo)
		right_fork = &(phil->back->philo[0].fork);
	else
		right_fork = &(phil->back->philo[phil->id].fork);
	pthread_mutex_lock(&phil->back->philo[phil->id - 1].fork);
	if (ft_diff(phil->back->time) >= (phil->t_death))
		return (right_fork);
	print_macro(FORK, phil);
	pthread_mutex_lock(right_fork);
	print_macro(FORK, phil);
	print_macro(EAT, phil);
	phil->t_death = ft_diff(phil->back->time) + phil->back->t_die;
	ft_atomic((long)phil->back->t_eat, phil->back->n_philo, phil);
	if (phil->back->n_times_eat)
		wait_for_eats(phil, right_fork);
	pthread_mutex_unlock(right_fork);
	pthread_mutex_unlock(&phil->back->philo[phil->id - 1].fork);
	return (NULL);
}

void	philo_routine(t_philo	*phil)
{
	if (phil->back->n_philo == 1)
	{
		printf("%ldms %d has taken a fork\n", ft_diff(phil->back->time),
			phil->id);
		while (1)
			;
	}
	while (!is_dead(phil) && !phil->back->check)
	{
		if (ft_kitchen(phil) != NULL)
			return ;
		pthread_mutex_lock(&phil->sleep);
		if (phil->back->check)
			return ;
		printf("%ldms %d is sleeping\n", ft_diff(phil->back->time), phil->id);
		ft_atomic((long)phil->back->t_sleep, phil->back->n_philo, phil);
		pthread_mutex_unlock(&phil->sleep);
		if (phil->back->check)
			return ;
		print_macro(THINK, phil);
	}
}

void	*thread_routine(void *data)
{
	t_philo	*phil;

	phil = (t_philo *)data;
	phil->t_death = ft_diff(phil->back->time) + phil->back->t_die;
	if (phil->id % 2 && phil->back->n_philo != 1)
		ft_atomic(phil->back->t_eat, phil->back->n_philo, phil);
	philo_routine(phil);
	return (NULL);
}
