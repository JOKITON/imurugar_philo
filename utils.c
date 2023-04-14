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

void	wait_for_eats(t_philo	*phil, pthread_mutex_t	*p_right_fork)
{
	phil->n_eats++;
	if (phil->back->n_times_eat != -1
		&& phil->n_eats == phil->back->n_times_eat)
	{
		pthread_mutex_unlock(&phil->back->philo[phil->id - 1].fork);
		pthread_mutex_unlock(p_right_fork);
		pthread_mutex_lock(&phil->death);
		phil->back->n_times_eat_checker++;
		while (phil->back->n_times_eat_checker != phil->back->n_philo)
			;
		pthread_mutex_unlock(&phil->death);
		phil->back->check = TRUE;
		return ;
	}
}

void	print_macro(int macro, t_philo	*philo)
{
	pthread_mutex_lock(&philo->back->print);
	if (macro == 1)
		printf("%ldms %d has taken a fork\n",
			ft_diff(philo->back->time), philo->id);
	else if (macro == 2)
		printf("%ldms %d is eating\n", ft_diff(philo->back->time), philo->id);
	else if (macro == 3)
		printf("%ldms %d is sleeping\n", ft_diff(philo->back->time), philo->id);
	else if (macro == 4)
		printf("%ldms %d is thinking\n", ft_diff(philo->back->time), philo->id);
	pthread_mutex_unlock(&philo->back->print);
}

void	init_philo(t_data	*data, int pos)
{
	pthread_mutex_init(&data->philo[pos].death, NULL);
	pthread_mutex_init(&data->philo[pos].fork, NULL);
	pthread_mutex_init(&data->philo[pos].sleep, NULL);
	data->philo[pos].id = pos + 1;
	data->philo[pos].n_eats = 0;
	data->philo[pos].back = data;
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
