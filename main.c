/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:11 by oukadir           #+#    #+#             */
/*   Updated: 2025/05/09 17:20:42 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	int		i;
	t_data	*data;

	i = 0;
	data = malloc(sizeof(t_data));
	parsing(ac, av, data);
	init_data(data, av);
	init_philosophers(data);
	create_threads(data);
	return (0);
}
