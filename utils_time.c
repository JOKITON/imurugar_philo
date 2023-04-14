/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_time.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 13:57:24 by jaizpuru          #+#    #+#             */
/*   Updated: 2023/04/12 14:13:29 by jaizpuru         ###   ########.fr       */
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
			usleep(ms * (philos / ms));
	else if (philos > 75 && philos <= 150)
		while (ft_diff((timer.tv_sec * 1000) + (timer.tv_usec / 1000)) < ms
			&& !is_dead(phil))
			usleep(ms * (philos * 3 / ms));
	else
		while (ft_diff((timer.tv_sec * 1000) + (timer.tv_usec / 1000)) < ms
			&& !is_dead(phil))
			usleep(ms / (ms / philos));
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
