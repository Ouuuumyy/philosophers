#include "philo.h"

void init_data(t_data *data, char **av)
{
    int i;
    i = 0;

    data->is_running = 1;
    data->num_of_philo = ft_atoi(av[1],data);
    data->time_to_die = ft_atoi(av[2], data);
    data->time_to_eat = ft_atoi(av[3], data);
    data->time_to_think = ft_atoi(av[4], data);
    data->must_eat_count = -1;
    if(av[5])
        data->must_eat_count = ft_atoi(av[5], data);
    data->start_time = get_time();
    data->philos = malloc(data->num_of_philo * sizeof(t_philo));
    data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
    while(i < data->num_of_philo)
    {
        pthread_mutex_init(&data->forks[i], NULL);
        i++;
    }
    pthread_mutex_init(&data->print_lock, NULL);
    pthread_mutex_init(&data->running_lock, NULL);
}

void init_philosophers(t_data *data)
{
    int i;
    i = 0;
    
    while(i < data->num_of_philo)
    {
        data->philos[i].meals = 0;
        data->philos[i].id = i + 1;
        data->philos[i].last_meal_time = data->start_time;
        data->philos[i].left_fork = &data->forks[i];
        data->philos[i].right_fork = &data->forks[(i + 1) % data->num_of_philo];
        data->philos[i].data = data;
        i++;
    }
}

void create_threads(t_data *data)
{
    int i;
    i = 0;

    pthread_create(&data->monitor_thread, NULL, &death_check_routine, data);
    while(i < data->num_of_philo)
    {
        if(pthread_create(&data->philos[i].thread, NULL, &philosopher_routine, &data->philos[i]) != 0)
            exit_error("can not create threads\n", data);
        usleep(100);
        i++;
    }
    pthread_join(data->monitor_thread, NULL);
    i = 0;
    while(i < data->num_of_philo)
    {
        pthread_join(data->philos[i].thread, NULL);
        i++;
    }
}
