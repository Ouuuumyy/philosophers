#include "philo.h"


void *philosopher_routine(void *arg)
{
    t_data *data;
    t_philo *philo;

    philo = (t_philo *)arg;
    data = philo->data;

    while(data->is_running == 1)
    {
        pthread_mutex_lock(&data->running_lock);
        if(!data->is_running)
        {
            pthread_mutex_unlock(&data->running_lock);
            free_data(data);
            exit(1);
        }
        pthread_mutex_unlock(&data->running_lock);
        if(!take_forks(philo, data))
            return NULL;
        eat(philo, data);
        check_eat_count(data, philo);
        sleep_and_think(philo, data);
    }
    return NULL;
}
void* check_eat_count(t_data *data, t_philo *philo)
{
    int i;

    i = 0;
    if (data->must_eat_count != -1)
    {
        if (philo->meals == data->must_eat_count) {
            pthread_mutex_lock(&data->print_lock);
            data->all_ate_enough ++;
            pthread_mutex_unlock(&data->print_lock);
        }
        if (data->all_ate_enough == data->num_of_philo) {
            pthread_mutex_lock(&data->running_lock);
            data->is_running = 0;
            pthread_mutex_unlock(&data->running_lock);
            //pthread_mutex_lock(&data->print_lock);
            printf("%lld all philosophers ate enough", get_time() - data->start_time);
            //pthread_mutex_unlock(&data->print_lock);
            free_data(data);
            exit(1);
        }
    }
}
void *death_check_routine(void *arg)
{
    t_data *data;
    int i;

    data = (t_data *)arg;
    while(data->is_running == 1)
    {
        i = 0;
        while(i < data->num_of_philo)
        {
            if(get_time() - data->philos[i].last_meal_time > data->time_to_die)
            {
                print_status(&data->philos[i], data, "died");
                pthread_mutex_lock(&data->running_lock);
                data->is_running = 0;
                pthread_mutex_unlock(&data->running_lock);
                free_data(data);
                exit(1);
            }
            i++;
        }
    }
    return NULL;
}

