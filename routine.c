/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:39 by oukadir           #+#    #+#             */
/*   Updated: 2025/05/11 20:04:47 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*one_philo(t_data *data, t_philo *philo)
{
	if (data->num_of_philo == 1)
	{
		ft_usleep(data->time_to_die, data);
		print_status(philo, data, "died");
		pthread_mutex_lock(&data->running_lock);
		data->is_running = 0;
		pthread_mutex_unlock(&data->running_lock);
		return (NULL);
	}
}

void	actions(t_data *data, t_philo *philo)
{
	take_forks(philo, data);
	eat(philo, data);
	check_eat_count(data, philo);
	sleep_and_think(philo, data);
}

void	*philosopher_routine(void *arg)
{
	t_data	*data;
	t_philo	*philo;
	int		s;

	philo = (t_philo *)arg;
	data = philo->data;
	one_philo(data, philo);
	while (1)
	{
		pthread_mutex_lock(&data->running_lock);
		s = data->is_running;
		pthread_mutex_unlock(&data->running_lock);
		if (!s)
			break ;
		pthread_mutex_lock(&data->running_lock);
		if (!data->is_running)
		{
			pthread_mutex_unlock(&data->running_lock);
			return (NULL);
		}
		pthread_mutex_unlock(&data->running_lock);
		actions(data, philo);
	}
	return (NULL);
}

void	*check_eat_count(t_data *data, t_philo *philo)
{
	int	i;

	i = 0;
	if (data->must_eat_count != -1)
	{
		if (philo->meals == data->must_eat_count)
		{
			pthread_mutex_lock(&data->print_lock);
			data->all_ate_enough++;
			pthread_mutex_unlock(&data->print_lock);
		}
		if (data->all_ate_enough == data->num_of_philo)
		{
			pthread_mutex_lock(&data->running_lock);
			data->is_running = 0;
			pthread_mutex_unlock(&data->running_lock);
			return (NULL);
		}
	}
}

void	*death_check_routine(void *arg)
{
	t_data	*data;
	int		i;

	data = (t_data *)arg;
	while (data->is_running == 1)
	{
		i = 0;
		while (i < data->num_of_philo)
		{
			if (get_time() - data->philos[i].last_meal_time > data->time_to_die)
			{
				print_status(&data->philos[i], data, "died");
				pthread_mutex_lock(&data->running_lock);
				data->is_running = 0;
				pthread_mutex_unlock(&data->running_lock);
				return (NULL);
			}
			i++;
		}
	}
	return (NULL);
}
