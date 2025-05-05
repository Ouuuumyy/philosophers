#include "philo.h"

long long get_time()
{
    struct timeval tv;
    int currnent_time;

    gettimeofday(&tv, NULL);
    currnent_time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
    return currnent_time;
}

void print_status(t_philo *philo, t_data *data, char *msg)
{
    long long timestamp;

    pthread_mutex_lock(&data->print_lock);
    timestamp = get_time() - data->start_time;
    printf("%lld, %d, %s\n", timestamp, philo->id, msg);
    pthread_mutex_unlock(&data->print_lock);
}

void check_running_lock(t_data *data)
{
    pthread_mutex_lock(&data->running_lock);
    if(!data->is_running)
    {
        pthread_mutex_unlock(&data->running_lock);
        return;
    }
    pthread_mutex_unlock(&data->running_lock);
}
// int	ft_usleep(useconds_t time)
// {
// 	u_int64_t	start;

// 	start = get_time();
// 	while ((get_time() - start) < time)
// 		usleep(time / 10);
// 	return (0);
// }
void take_forks(t_philo *philo, t_data *data)
{
    check_running_lock(data);
    if(philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, data, "has taken a fork");
        if(!data->is_running)
        {
            pthread_mutex_unlock(philo->right_fork);
            return;
        }
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, data, "has taken a fork");
    }
    else
    {
        pthread_mutex_lock(philo->left_fork);
        print_status(philo, data, "has taken a fork");
        if(!data->is_running)
        {
            pthread_mutex_unlock(philo->left_fork);
            return;
        }
        pthread_mutex_lock(philo->right_fork);
        print_status(philo, data, "has taken a fork");
    }
}

void eat(t_philo *philo, t_data *data)
{
    check_running_lock(data);
    print_status(philo, data, "is eating");
    philo->last_meal_time = get_time();
    usleep(data->time_to_eat * 1000);
    philo->meals++;
}

void sleep_and_think(t_philo *philo, t_data *data)
{
    check_running_lock(data);
    print_status(philo, data, "is sleeping");
    usleep(data->time_to_think * 1000);
    print_status(philo, data, "is thinking");
}

