/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imurugar <imurugar@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 19:01:26 by imurugar          #+#    #+#             */
/*   Updated: 2023/04/14 19:55:42 by imurugar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clear_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_philo)
	{
		pthread_mutex_destroy(&(data->philo[i].fork));
		i++;
	}
	pthread_mutex_destroy(&data->death);
	pthread_mutex_destroy(&data->print);
	free(data->shared_fork);
	free(data->philo);
}
