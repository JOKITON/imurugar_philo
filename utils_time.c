/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:57:24 by jaizpuru          #+#    #+#             */
/*   Updated: 2023/04/14 15:28:41 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atomic(long ms, int philos, t_philo	*phil)
{
	struct timeval	timer;

	gettimeofday(&timer, NULL);
	if (philos > 150)
		while (ft_diff((timer.tv_sec * 1000) + (timer.tv_usec / 1000)) < ms
			&& !is_dead(phil))
			usleep(750);
	else if (philos > 75 && philos <= 150)
		while (ft_diff((timer.tv_sec * 1000) + (timer.tv_usec / 1000)) < ms
			&& !is_dead(phil))
			usleep(500);
	else
		while (ft_diff((timer.tv_sec * 1000) + (timer.tv_usec / 1000)) < ms
			&& !is_dead(phil))
			usleep(250);
	return (0);
}

long	ft_diff(long before)
{
	struct timeval	tp;
	long			result;

	gettimeofday(&tp, NULL);
	result = (tp.tv_sec * 1000) + (tp.tv_usec / 1000);
	result = result - before;
	return (result);
}
