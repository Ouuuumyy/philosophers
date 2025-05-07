#include "philo.h"

int take_forks(t_philo *philo, t_data *data)
{
    pthread_mutex_t *first_fork;
    pthread_mutex_t *second_fork;
    
    if(philo->id % 2)
    {
        first_fork = philo->right_fork;
        second_fork = philo->left_fork;
    }
    else
    {
        first_fork = philo->left_fork;
        second_fork = philo->right_fork;
    }
    pthread_mutex_lock(first_fork);
    if(!data->is_running)
    {
        pthread_mutex_unlock(first_fork);
        return (0);
    }
    pthread_mutex_lock(second_fork);
    if(!data->is_running)
    {
        pthread_mutex_unlock(first_fork);
        return (0);
    }
    return(1);
}


void eat(t_philo *philo, t_data *data)
{
    print_status(philo, data, "is eating");
    philo->last_meal_time = get_time();
    ft_usleep(data->time_to_eat, data);
    philo->meals++;
    pthread_mutex_unlock(philo->left_fork);
    pthread_mutex_unlock(philo->right_fork);
}

void sleep_and_think(t_philo *philo, t_data *data)
{
    print_status(philo, data, "is sleeping");
    ft_usleep(data->time_to_sleep, data);
    print_status(philo, data, "is thinking");
}