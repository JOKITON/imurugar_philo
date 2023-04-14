/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 11:18:21 by hedgedog          #+#    #+#             */
/*   Updated: 2023/04/14 15:24:42 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_args(t_data	*data)
{
	printf("				START TIME -> %ld\n", data->time);
	printf("				PHILOSOPHERS -> %d\n", data->n_philo);
	printf("				TME TO DIE -> %ld\n", data->t_die);
	printf("				TME TO EAT -> %ld\n", data->t_sleep);
	printf("				TME TO SLEEP -> %ld\n", data->t_eat);
	if (data->n_times_eat != -1)
		printf("				TMES TO EAT -> %d\n", data->n_times_eat);
}

int	get_args(t_data	*data, char	**args)
{
	pthread_mutex_init(&data->print, NULL);
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
	data->n_times_eat_checker = 0;
	return (EXIT_SUCCESS);
}

void	end_philo(t_data	*data)
{
	int	i;

	i = 0;
	if (data->n_philo > 1)
	{
		while (!is_dead(&data->philo[1]))
			if (data->check == TRUE)
				break ;
	}
	else
	{
		while (!is_dead(&data->philo[0]))
			if (data->check == TRUE)
				break ;
	}
	while (i < data->n_philo)
	{
		destroy_mutexes(&data->philo[i]);
		pthread_detach(data->philo[i++].thread);
	}
}

int	get_philo(t_data	*data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(&data->print);
	while (i < data->n_philo)
	{
		init_philo(data, i);
		if (pthread_create(&data->philo[i].thread, NULL, thread_routine,
				&(data->philo[i])) != 0)
			return (EXIT_FAILURE);
		i++;
	}
	pthread_mutex_unlock(&data->print);
	usleep(1000);
	end_philo(data);
	return (EXIT_SUCCESS);
}

int	main(int argc, char	**argv)
{
	t_data			data;

	if (argc < 5 || argc > 6)
	{
		write(2, "Error\n", 7);
		return (EXIT_FAILURE);
	}
	if (get_args(&data, argv) != 0)
		return (write(2, "Error\n", 7));
	if (get_philo(&data) == 1)
		return (write(2, "Thread creation failed\n", 25));
	free(data.philo);
}
