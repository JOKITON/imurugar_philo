/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:18:21 by hedgedog          #+#    #+#             */
/*   Updated: 2023/04/14 15:28:28 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_args(t_data	*data, char	**args)
{
	pthread_mutex_init(&data->print, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->n_philo = ft_atoi(args[1]);
	data->forks = data->n_philo;
	data->philo = (t_philo *)malloc(sizeof(t_philo) * data->n_philo);
	data->t_die = (time_t)ft_atoi(args[2]);
	data->t_eat = (time_t)ft_atoi(args[3]);
	data->t_sleep = (time_t)ft_atoi(args[4]);
	data->check = FALSE;
	gettimeofday(&data->start, NULL);
	data->time = (data->start.tv_sec * 1000) + (data->start.tv_usec / 1000);
	if (data->n_philo < 1 || data->forks < 0 || data->t_die < 0
		|| data->t_sleep < 0 || data->t_eat < 0)
		return (free (data->philo), EXIT_FAILURE);
	if (args[5])
	{
		if (ft_atoi(args[5]) <= 0)
			return (free (data->philo), EXIT_FAILURE);
		data->n_times_eat = ft_atoi(args[5]);
	}
	else
		data->n_times_eat = -1;
	data->shared_fork = malloc(sizeof(char) * data->n_philo);
	return (EXIT_SUCCESS);
}

int	join_threads(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->n_philo)
	{
		if (pthread_join(data->philo[i].thread, NULL) != 0)
		{
			printf("Thread join failed at philos\n");
			return (0);
		}
	}
	return (1);
}

int	get_philo(t_data *data)
{
	int	i;

	i = 0;
	init_philos(data);
	while (i < data->n_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL, thread_routine,
				&(data->philo[i])) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	join_threads(data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char	**argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (EXIT_FAILURE);
	}
	if (get_args(&data, argv) != 0)
		return (printf("Error\n"));
	if (get_philo(&data) == 1)
		return (printf("Thread creation failed\n"));
	clear_all(&data);
	return (EXIT_SUCCESS);
}
