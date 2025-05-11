/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:07 by oukadir           #+#    #+#             */
/*   Updated: 2025/05/11 20:21:24 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutexes(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
	{
		free(data->philos);
		exit_error("failed allocation for forks", data);
	}
	while (i < data->num_of_philo)
	{
		pthread_mutex_init(&data->forks[i], NULL);
		i++;
	}
	pthread_mutex_init(&data->print_lock, NULL);
	pthread_mutex_init(&data->running_lock, NULL);
}

void	init_data(t_data *data, char **av)
{
	data->is_running = 1;
	data->num_of_philo = ft_atoi(av[1], data);
	data->time_to_die = ft_atoi(av[2], data);
	data->time_to_eat = ft_atoi(av[3], data);
	data->time_to_sleep = ft_atoi(av[4], data);
	data->must_eat_count = -1;
	data->all_ate_enough = 0;
	if (av[5])
		data->must_eat_count = ft_atoi(av[5], data);
	data->start_time = get_time();
	data->philos = malloc(data->num_of_philo * sizeof(t_philo));
	if (!data->philos)
		exit_error("failed allocation for philos", data);
	init_mutexes(data);
}

void	init_philosophers(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_of_philo)
	{
		data->philos[i].meals = 0;
		data->philos[i].id = i + 1;
		data->philos[i].last_meal_time = data->start_time;
		data->philos[i].left_fork = &data->forks[i];
		if (i == data->num_of_philo - 1)
			data->philos[i].right_fork = &data->forks[0];
		else
			data->philos[i].right_fork = &data->forks[i + 1];
		data->philos[i].data = data;
		i++;
	}
}

void	create_threads(t_data *data)
{
	int	i;

	i = 0;
	pthread_create(&data->monitor_thread, NULL, &death_check_routine, data);
	while (i < data->num_of_philo)
	{
		if (pthread_create(&data->philos[i].thread, NULL, &philosopher_routine,
				&data->philos[i]) != 0)
			exit_error("can not create threads", data);
		usleep(100);
		i++;
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	pthread_join(data->monitor_thread, NULL);
	free_data(data);
}
