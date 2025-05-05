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
            break;
        }
        pthread_mutex_unlock(&data->running_lock);
        take_forks(philo, data);
        eat(philo, data);
        pthread_mutex_unlock(philo->left_fork);
        pthread_mutex_unlock(philo->right_fork);
        sleep_and_think(philo, data);
    }
    return NULL;
}
void* check_eat_count(t_data *data)
{
    if (data->must_eat_count != -1) {
        int all_ate_enough = 1;
        for (int i = 0; i < data->num_of_philo; i++) {
            if (data->philos[i].meals < data->must_eat_count) {
                all_ate_enough = 0;
                break;
            }
        }
        if (all_ate_enough) {
            pthread_mutex_lock(&data->running_lock);
            data->is_running = 0;
            pthread_mutex_unlock(&data->running_lock);
            print_status(&data->philos[0], data, "all philosophers ate enough");
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
                exit(1);
                // pthread_mutex_lock(&data->running_lock);
                // data->is_running = 0;
                // pthread_mutex_unlock(&data->running_lock);
                // return NULL;
            }
            i++;
        }
        check_eat_count(data);
        usleep(100);
    }
    return NULL;
}

