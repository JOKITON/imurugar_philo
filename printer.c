/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:00:07 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/14 19:44:20 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_macro(int macro, t_philo	*philo)
{
	pthread_mutex_lock(&philo->back->print);
	if (check_any_die(philo))
	{
		pthread_mutex_unlock(&philo->back->print);
		return ;
	}
	if (macro == 1)
		printf("%ldms %d has taken a fork\n",
			ft_diff(philo->back->time), philo->id);
	else if (macro == 2)
		printf("%ldms %d is eating\n", ft_diff(philo->back->time), philo->id);
	else if (macro == 3)
		printf("%ldms %d is sleeping\n", ft_diff(philo->back->time), philo->id);
	else if (macro == 4)
		printf("%ldms %d is thinking\n", ft_diff(philo->back->time), philo->id);
	else if (macro == 5)
	{
		pthread_mutex_lock(&philo->back->death);
		philo->back->check = TRUE;
		pthread_mutex_unlock(&philo->back->death);
		printf("%ldms %d died\n", ft_diff(philo->back->time), philo->id);
	}
	pthread_mutex_unlock(&philo->back->print);
}
