/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:59:46 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/14 19:46:30 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_dead(t_philo	*philo)
{
	if (!philo->t_death || !philo->back->time)
		return (0);
	if (check_any_die(philo))
		return (1);
	if (ft_diff(philo->back->time) >= (philo->t_death))
	{
		print_macro(DIE, philo);
		return (1);
	}
	return (0);
}

int	check_any_die(t_philo	*philo)
{
	int	any_dead;

	pthread_mutex_lock(&(philo->back->death));
	any_dead = philo->back->check;
	pthread_mutex_unlock(&(philo->back->death));
	return (any_dead);
}
