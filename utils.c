/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 10:36:55 by jaizpuru          #+#    #+#             */
/*   Updated: 2023/04/13 16:16:54 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philos(t_data	*data)
{
	int	pos;

	pos = 0;
	while (pos < data->n_philo)
	{
		pthread_mutex_init(&data->philo[pos].fork, NULL);
		data->philo[pos].id = pos + 1;
		data->philo[pos].n_eats = 0;
		data->philo[pos].back = data;
		data->philo[pos].forks_in_hand = 0;
		data->shared_fork[pos] = 0;
		pos++;
	}
}

int	ft_atoi(const char *str)
{
	int				loop;
	unsigned int	box;
	int				negative;

	box = 0;
	loop = 0;
	negative = 1;
	while (str[loop] == '\n' || str[loop] == '\t' || str[loop] == '\v'
		|| str[loop] == ' ' || str[loop] == '\f' || str[loop] == '\r')
			loop++;
	if (str[loop] == '-' || str[loop] == '+')
	{
		if (str[loop++] == '-')
		{
			negative = -negative;
		}
	}
	while (str[loop] >= '0' && str[loop] <= '9')
	{
		box = (box * 10) + str[loop] - '0';
		loop++;
	}
	return ((int)(box * negative));
}
