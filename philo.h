/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oukadir <oukadir@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:19:29 by oukadir           #+#    #+#             */
/*   Updated: 2025/05/09 17:19:32 by oukadir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_philo
{
	int				id;
	long long		last_meal_time;
	int				meals;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_t		thread;
	struct s_data	*data;
}					t_philo;

typedef struct s_data
{
	int				num_of_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long long		start_time;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	running_lock;
	pthread_t		monitor_thread;
	t_philo			*philos;
	int				is_running;
	int				all_ate_enough;
}					t_data;

void				check_running_lock(t_data *data);
int					ft_atoi(const char *str, t_data *data);
void				*philosopher_routine(void *arg);
void				*death_check_routine(void *arg);
int					take_forks(t_philo *philo, t_data *data);
long long			get_time(void);
void				print_status(t_philo *philo, t_data *data, char *msg);
void				parsing(int ac, char **av, t_data *data);
void				exit_error(char *str, t_data *Data);
void				init_philosophers(t_data *data);
void				create_threads(t_data *data);
void				init_data(t_data *data, char **av);
void				sleep_and_think(t_philo *philo, t_data *data);
void				eat(t_philo *philo, t_data *data);
void				free_data(t_data *data);
void				ft_usleep(long time, t_data *data);
void				*check_eat_count(t_data *data, t_philo *philo);
#endif