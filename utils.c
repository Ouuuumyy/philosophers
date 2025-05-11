/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:46 by oukadir           #+#    #+#             */
/*   Updated: 2025/05/11 18:37:28 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit_error(char *str, t_data *data)
{
	printf("Error: %s\n", str);
	if (data && data->forks && data->philos)
		free_data(data);
	else if (data)
		free(data);
	exit(1);
}

long long	get_time(void)
{
	struct timeval	tv;
	int				currnent_time;

	gettimeofday(&tv, NULL);
	currnent_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (currnent_time);
}

void	print_status(t_philo *philo, t_data *data, char *msg)
{
	long long	timestamp;

	pthread_mutex_lock(&data->print_lock);
	if (data->is_running)
	{
		timestamp = get_time() - data->start_time;
		printf("%lld %d %s\n", timestamp, philo->id, msg);
	}
	pthread_mutex_unlock(&data->print_lock);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	if (data->forks)
	{
		while (i < data->num_of_philo)
		{
			pthread_mutex_destroy(&data->forks[i]);
			i++;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&data->print_lock);
	pthread_mutex_destroy(&data->running_lock);
	if (data->philos)
		free(data->philos);
	free(data);
}

void	ft_usleep(long time, t_data *data)
{
	long	start;

	start = get_time();
	while (data->is_running && get_time() - start < time)
		usleep(200);
}
