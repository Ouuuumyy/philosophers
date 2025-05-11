/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:18 by oukadir           #+#    #+#             */
/*   Updated: 2025/05/11 20:21:57 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(const char *str, t_data *data)
{
	long	n;
	int		i;
	int		min;

	n = 0;
	i = 0;
	while (str[i] && (str[i] == 32 || (str[i] >= 9 && str[i] <= 13)))
		i++;
	while (str[i] && (str[i] >= '0' && str[i] <= '9'))
	{
		n = n * 10 + str[i++] - 48;
		if (n > INT_MAX)
			exit_error("argument exceeds max int", data);
	}
	return ((int)n);
}

void	parsing(int ac, char **av, t_data *data)
{
	int	i;
	int	num;

	i = 1;
	if (ac < 5 || ac > 6)
		exit_error("uncorrect number of arguments", data);
	while (i < ac)
	{
		if (is_digit(av[i]) != 0)
			exit_error("you must enter a positive number", data);
		num = ft_atoi(av[i], data);
		if (i == 1 && num >= 200)
			exit_error("you entered more than 200 philosopher", data);
		if (num == 0)
			exit_error("arguments must be > 0", data);
		i++;
	}
}
